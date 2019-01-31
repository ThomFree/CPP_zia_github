# CLI

## Introduction
In order to ease the navigation between several sites, we decided to create a CLI.

## Commands
The console is displayed with a `>` Here's an exhaustive list of what you can do on the CLI :

- `create_website <website_name> <ip> <port>` : create a new website with the name you give in paramater. The prompt will be modified with the name of the website, example : `website_name >` 
- `enter <website_name>` : entering in configuration mode for the website you give in parameter. Prompt modified with the `website_name`.
- `back` : come back to the main menu and display `>` .
- `list` : list status of all websites created.
- `stop` : quit the server.
- `help` : display the command list.

### Config commands
The following commands must be used within the website. It means that you can't use these  without entering beforehand a website with the `enter` command.

- `delete_website` : delete website already created. The `back` command is executed afterwards.
- `start` : start the website.
- `pause` : stop the website.
- `status` : display the actual status of the website.
- `enable <module_name>` : enable the module specified in parameter. Not limited to one parameter.
- `disable <module_name>` : disable the module specified in parameter. Not limited to one parameter.
- `reload <module_name>` : reload the module specified in parameter.

The next command must not be used within a website. You can execute this command when your prompt is only displaying `>` .
- `reload_all <module_name>` :  reload the given module for every site where the module is. Not limited to one parameter.

