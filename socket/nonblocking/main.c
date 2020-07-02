#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

#define SERVER_PORT 12345

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
    int i, len, rc, on = 1;
    int listen_sd, max_sd, new_sd;
    int desc_ready, end_server = FALSE;

    int close_conn;
    char buffer[80];
    struct sockaddr_in addr;
    struct timeval      timeout;
    fd_set              master_set, working_set;

    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }

    rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

    if (rc < 0)
    {
        perror("setsockopt() failed");
        exit(-1);
    }

    rc = ioctl(listen_sd, FIONBIO, (char *)&on);

    if( rc < 0 )
    {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(SERVER_PORT);

    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));

    if ( rc < 0 )
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }

    rc = listen(listen_sd, 32);
    if( rc < 0 )
    {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }

    FD_ZERO(&master_set);
    max_sd = listen_sd;
    FD_SET(listen_sd, &master_set);

    /*
      Initialize the timeval struct to 3 minutes. 
      If no activity after 3 minutes this program will end.
    */
    timeout.tv_sec  = 3 * 60;
    timeout.tv_usec = 0;

    do {

        /* Copy the master fd_set over to the working fd_set.     */
        memcpy(&working_set, &master_set, sizeof(master_set));

        /* Call select() and wait 3 minutes for it to complete.   */
        printf("Waiting on select()...\n");
        rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);

        if( rc < 0 )
        {
            perror("select() failed");
            break;
        }

        if ( 0 == rc )
        {
            printf("  select() timed out.  End program.\n");
            break;
        }
        
        desc_ready = rc;

        for (i=0; i <= max_sd && desc_ready > 0; ++i)
        {
            /*******************************************************/
            /* Check to see if this descriptor is ready            */
            /*******************************************************/
            if(FD_ISSET(i, &working_set))
            {
                /****************************************************/
                /* A descriptor was found that was readable - one   */
                /* less has to be looked for.  This is being done   */
                /* so that we can stop looking at the working set   */
                /* once we have found all of the descriptors that   */
                /* were ready.                                      */
                /****************************************************/
                desc_ready -= 1;

                /****************************************************/
                /* Check to see if this is the listening socket     */
                /****************************************************/
                if (i == listen_sd)
                {
                    printf("  Listening socket is readable\n");
                    /*************************************************/
                    /* Accept all incoming connections that are      */
                    /* queued up on the listening socket before we   */
                    /* loop back and call select again.              */
                    /*************************************************/
                    do 
                    {
                        /**********************************************/
                        /* Accept each incoming connection.  If       */
                        /* accept fails with EWOULDBLOCK, then we     */
                        /* have accepted all of them.  Any other      */
                        /* failure on accept will cause us to end the */
                        /* server.                                    */
                        /**********************************************/
                        new_sd = accept(listen_sd, NULL, NULL);
                        if (new_sd < 0)
                        {
                            if (errno != EWOULDBLOCK)
                            {
                                perror("  accept() failed");
                                end_server = TRUE;
                            }
                            break;
                        }

                        /**********************************************/
                        /* Add the new incoming connection to the     */
                        /* master read set                            */
                        /**********************************************/
                        printf("  New incoming connection - %d\n", new_sd);
                        FD_SET(new_sd, &master_set);
                        if (new_sd > max_sd)
                            max_sd = new_sd;

                    } while (new_sd != -1);
                } 
                /****************************************************/
                /* This is not the listening socket, therefore an   */
                /* existing connection must be readable             */
                /****************************************************/
                else 
                {
                    printf("  Descriptor %d is readable\n", i);
                    close_conn = FALSE;
                    /*************************************************/
                    /* Receive all incoming data on this socket      */
                    /* before we loop back and call select again.    */
                    /*************************************************/
                    do
                    {
                        /**********************************************/
                        /* Receive data on this connection until the  */
                        /* recv fails with EWOULDBLOCK.  If any other */
                        /* failure occurs, we will close the          */
                        /* connection.                                */
                        /**********************************************/
                        rc = recv(i, buffer, sizeof(buffer), 0);
                        if ( rc < 0 )
                        {
                            if (errno != EWOULDBLOCK)
                            {
                                perror("  recv() failed");
                                close_conn = TRUE;
                            }
                            break;
                        }

                        /**********************************************/
                        /* Check to see if the connection has been    */
                        /* closed by the client                       */
                        /**********************************************/
                        if (rc == 0)
                        {
                            printf("  Connection closed\n");
                            close_conn = TRUE;
                            break;
                        }

                        /**********************************************/
                        /* Data was received                          */
                        /**********************************************/
                        len = rc;
                        printf("  %d bytes received\n", len);


                        /**********************************************/
                        /* Echo the data back to the client           */
                        /**********************************************/
                        rc = send(i, buffer, len, 0);
                        if ( rc < 0 ) 
                        {
                            perror("send() failed");
                            close_conn = TRUE;
                            break;
                        }



                    } while (TRUE);

                    if( close_conn ) 
                    {
                        close(i);
                        FD_CLR(i, &master_set);

                        if( i == max_sd ) 
                        {
                            while ( FD_ISSET(max_sd, &master_set)  == FALSE)
                                max_sd -= 1;
                        }
                    }

                } /* End of existing connection is readable */

            } /* End of if (FD_ISSET(i, &working_set)) */
        } /* End of loop through selectable descriptors */

    } while ( FALSE == end_server );


    /*************************************************************/
    /* Clean up all of the sockets that are open                 */
    /*************************************************************/
    for ( i=0; i <= max_sd; ++i)
    {
        if(FD_ISSET(i ,&master_set))
            close(i);
    }

    return 0;
}

/*
Reference
- [Example: Nonblocking I/O and select()](https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_74/rzab6/xnonblock.htm)
*/
