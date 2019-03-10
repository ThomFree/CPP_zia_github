--- HOW TO USE GuiLogger ---

You need to add a module in the config file.
Here is an example on how you add the module in your config:

{
  "name": "BasicHttpSite",
  "port": 8080,
  "modules": {
    "GuiLogger": {
      "path": "./build/lib/libmod_guiLogger.so"
    }
  }
}

The name "GuiLogger" is important. "path" is required in order to load the module.
In the configuration of your module, you can also add a "logPath" variable.
The "logPath" can be either a path to a directory or a file.
The module will create directories automatically.
The "logPath" by default is "./etc/zia/log/".
Here is the complete example :

{
  "name": "BasicHttpSite",
  "port": 8080,
  "modules": {
    "GuiLogger": {
      "path": "./build/lib/libmod_guiLogger.so",
      "logPath": "./etc/zia/log/"
    }
  }
}
