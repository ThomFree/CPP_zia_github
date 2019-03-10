--- HOW TO USE HTTP Module ---

You need to add a module in the config file.
Here is an example on how you add the module in your config:

{
  "name": "BasicHttpSite",
  "port": 8080,
  "modules": {
    "Http": {
      "path": "./build/lib/libmod_guiLogger.so"
    }
  }
}

The name "Http" is important. "path" is required in order to load the module.
In the configuration of your module, you can also add a "websitePath" variable.
The "websitePath" can be either a path to a directory or a file.
The module will create directories automatically.
The "websitePath" by default is "./etc/zia/www/", and will get the "index.html" file.
Here is the complete example :

{
  "name": "BasicHttpSite",
  "port": 8080,
  "modules": {
    "Http": {
      "path": "./build/lib/libmod_guiLogger.so",
      "websitePath": "./etc/zia/log/"
    }
  }
}
