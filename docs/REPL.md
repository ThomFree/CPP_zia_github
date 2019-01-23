# REPL

## Introduction:
The goal of the REPL is to make interaction between user and server easy. There is two part of project that can interact with user:

- the core (for example to add module, stop the server ...)
- any module (for example to manage it)

The REPL is composed of multiple part:

<img src="https://i.imgur.com/wP1t2bn.png](https://i.imgur.com/wP1t2bn.png">

- **the standard input reader:** it wait on standard input event: for user type command or for response come from mediator after comand is entered
- **the parser:** it parse all tokens of command to serialize it as `ReplCommand` and send this to the mediator
- **the mediator:** it route the command to appropriate component (the **Core** or any related module)
- **the response formatter:** it take response of the command sent by mediator as `ReplResponse` and format it into human readable string to sent-it to standard output

## Syntax:
The syntax is universal for all commands and it's composed of three **space delimited** elements:

<img src="https://i.imgur.com/y1kmGJD.png">


- it begin with the **prefix**: it define the command scope, if it's **Core** command, the prefix is always **server**, otherwise the **prefix** can be the target module name. *(it cannot contain any space, the convention is to use snake case)*.
- it continue with the **command name**, it's an unique string for the scope that identify the command and what it do *(it cannot contain any space, the convention is to use snake case)*.
- it end with optionnal command arguments, also space delimited


## Core commands:

All Core commands are into **server** scope.

### Website commands:

- `create_website {name} {host} {port}`: Create new website identified by **name** that will listen into specified **host** and **port**
- `list_websites`: List all created websites with associated data
- `remove_website {name}`: Remove specified website
- `enable_website {name}`: Enable and start specified website
- `disable_website {name}`: Disable and stop specified website

### Module commands:

- `plug_module {website_name} {module_name}`: Plug specified module for specified website 
- `unplug_module {website_name} {module_name}`: Un-plug specified module for specified website
- `reload_module {website_name} {module_name OR *}`: Reload specified module for specified website or for all websites
- `stop`: Exit the server