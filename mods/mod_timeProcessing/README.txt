--- HOW TO USE TimeProcessing ---

You need to add a module in the config file.
Here is an example on how you add the module in your config:

{
  "name": "BasicHttpSite",
  "port": 8080,
  "modules": {
    "TimeProcessing": {
      "path": "./build/lib/libmod_timeProcessing.so"
    }
  }
}

The name "TimeProcessing" is important. "path" is required in order to load the module.
In the configuration of your module, you can also add a "timeMS" variable where you have to put
an int to indicate the time you want the program to wait for each stage of each hook.
The "timeMS" is in miliseconds.
The "timeMS" by default is 50.
Here is the complete example :

{
  "name": "BasicHttpSite",
  "port": 8080,
  "modules": {
    "TimeProcessing": {
      "path": "./build/lib/libmod_timeProcessing.so",
      "timeMS": 50
    }
  }
}