# CLI

## Introduction
In order to ease the navigation between several sites, we decided to create a CLI.

## Commands
The console is displayed with a `>` Here's an exhaustive list of what you can do on the CLI :

- `create_website <website_name> <ip> <port>` : create a new website with the name you give in paramater. The prompt will be modified with the name of the website, example : `website_name >` 
- `config_website <website_name>` : entering in configuration mode for the website you give in parameter. Prompt modified with the `website_name`.
- `delete_website <website_name>` : delete website already created. Give the Website name in parameter.
- `back` : come back to the main menu and display `>` .

The following commands can be used within the website. It means that you can bypass the `website_name` parameter if you are already in.

- `start <website_name>` : start the website given in parameter.
- `pause <website_name>` : stop the website given in parameter.
- `enable <module_name> <website_name>` : enable the module specified in parameter. Not limited to one module per command.
- `disable <module_name> <website_name>` : disable the module specified in parameter. Not limited to one module per command.
- `reload <module_name> <website_name>` : reload the module specified in parameter within the given website.

--
- `reload_all <module_name>` :  reload the given module for every site where the module is.
- `stop` : quit the server.
- `help` : display the command list.

