# Software Initiation 

``` go
// ./main/main.go

import (
    // ...
    // This line [initiate][1]
	_ "v2ray.com/core/main/distro/all"
)

// ...


func main() {

    // ...
    // Get software instance 
    server, err := startV2Ray()
    // ...

    // Start software instance 
    if err := server.Start(); err != nil {
		fmt.Println("Failed to start", err)
		os.Exit(-1)
    }
    // ...
}


func startV2Ray() {
    // ...
    // Load software configuration into memory
    config, err := core.LoadConfig(GetConfigFormat(), configFiles[0], configFiles) 
    // ...

    // Prepare software instance based on configuration
    server, err := core.New(config)
    // ...
}

```


> [What does an underscore in front of an import statement mean?](https://stackoverflow.com/questions/21220077/what-does-an-underscore-in-front-of-an-import-statement-mean)


## Load software configuration into memory 

More logic related to loading from json configuration file.

``` go
// config.go
func LoadConfig(formatName string, filename string, input interface{}) (*Config, error) {
    // ...
    if f, found := configLoaderByName[formatName]; found {
		return f.Loader(input)
    }
    // ...
}
```

``` go
// ./main/json/config_json.go
func init() {
    // RegisterConfigLoader 
    // Register load function at the software initiation 
    // This pattern used by more object creations inside the software.
	common.Must(core.RegisterConfigLoader(&core.ConfigFormat{
		Name:      "JSON",
		Extension: []string{"json"},
		Loader: func(input interface{}) (*core.Config, error) {
			switch v := input.(type) {
			case cmdarg.Arg:
				r, err := confloader.LoadExtConfig(v)
				if err != nil {
					return nil, newError("failed to execute v2ctl to convert config file.").Base(err).AtWarning()
				}
				return core.LoadConfig("protobuf", "", r)
			case io.Reader:
				return serial.LoadJSONConfig(v)
			default:
				return nil, newError("unknow type")
			}
		},
	}))
}

```

``` go
// ./infra/conf/serial/loader.go


// ...
func LoadJSONConfig(reader io.Reader) (*core.Config, error) {
	jsonConfig, err := DecodeJSONConfig(reader)
	if err != nil {
		return nil, err
	}

    // Convert json format configuration into protobuf format
	pbConfig, err := jsonConfig.Build()
	if err != nil {
		return nil, newError("failed to parse json config").Base(err)
	}

	return pbConfig, nil
}
```

``` go
// ./infra/conf/v2ray.go

// Config data structure
type Config struct {
	Port            uint16                 `json:"port"` // Port of this Point server. Deprecated.
	LogConfig       *LogConfig             `json:"log"`
	RouterConfig    *RouterConfig          `json:"routing"`
	DNSConfig       *DnsConfig             `json:"dns"`
	InboundConfigs  []InboundDetourConfig  `json:"inbounds"`
	OutboundConfigs []OutboundDetourConfig `json:"outbounds"`
	InboundConfig   *InboundDetourConfig   `json:"inbound"`        // Deprecated.
	OutboundConfig  *OutboundDetourConfig  `json:"outbound"`       // Deprecated.
	InboundDetours  []InboundDetourConfig  `json:"inboundDetour"`  // Deprecated.
	OutboundDetours []OutboundDetourConfig `json:"outboundDetour"` // Deprecated.
	Transport       *TransportConfig       `json:"transport"`
	Policy          *PolicyConfig          `json:"policy"`
	Api             *ApiConfig             `json:"api"`
	Stats           *StatsConfig           `json:"stats"`
	Reverse         *ReverseConfig         `json:"reverse"`
}

// Convert into protobuf format configuration
func (c *Config) Build() (*core.Config, error) {
    // ...
}
```

## Prepare software instance based on configuration

``` go
// ./v2ray.go

// ...
func New(config *Config) (*Instance, error) {
	var server = &Instance{ctx: context.Background()}

	err, done := initInstanceWithConfig(config, server)
	if done {
		return nil, err
	}

	return server, nil
}
// ...


// Initiate software insance base on configuration
func initInstanceWithConfig(config *Config, server *Instance) (error, bool) {
    // ...
}
// ...


```

## Start instance 

``` go
// ./v2ray.go

// ...
func (s *Instance) Start() error {
	s.access.Lock()
	defer s.access.Unlock()

	s.running = true
	for _, f := range s.features {
		if err := f.Start(); err != nil {
			return err
		}
	}

	newError("V2Ray ", Version(), " started").AtWarning().WriteToLog()

	return nil
}

```


# Dataflow

## Intorduce "inbound->dispatch->outbound" dataflow

### Inbound handler initiation


2. Introduce "outbound->Internet->inbound" dataflow




# Reference 