# 🤖 The Zia web server architecture

## Introduction
The goal of the Zia web server is to handle multiple websites with asynchronous connections using modules to craft the response from the request.

The server's aim is to be fully customizable thanks to configuration files. It also doesn't need to be restarted thanks to a **file watcher system**, and the user can interact directly with it using a **command line interface (CLI)**.

<img src="https://i.imgur.com/kA7QyJR.png">

The entry point of the Zia is where all parts of the project are setup. The entry point is obviously into the **main thread**.


## Shell

At the startup of Zia, a shell is started in the **main thread** that allows the user to type commands to interact with web server. The shell waits for data, reading **stdin** asynchronously, then it sends this data to the **parser**.

The parser is the main part of the shell, his goal is to translate human written commands into web server actions.

When in the shell, the user can choose which **website** to interact with (starting, stopping, changing it's configutation files etc..).

Likewise, when interacting with a website, the user can choose which **module** to interact with (loading, unload, changing it's configuration files etc...)

*(TODO : mettre des exemples, peut-être un schéma)*

When a command is parsed, the serialized command is **dispatched** to the appropriated website (module handling) or to the **websites manager** if it's its general purpose.

## Configuration watcher

At the startup of Zia, a command watcher is starter into a **specific watcher thread**. *(TODO: or maybe asynchronously into main thread ?)*

The command watcher waits for events to come from a filesystem that indicates the modification of a configuration file.

When a configuration file is modified, the watcher makes parsing operations into the target file, and **dispatches** the new configuration data to the appropriated website or to the **websites manager** if it's its general purpose.

## *TODO* Dispatcher
Need some reflection on the design pattern to use for communication across all entities: **Shell**, **Configuration watcher**, **Websites manager** and all **Websites**.

We need a robust and generic way to make this communication safe and easy across all entities of the Zia web server.
A **concurrent bounded queue** with a target notification system can be great and easy to use.

## Websites manager

The websites manager is the most important part of the web server. His first goal is to manage lifetime of websites:

- 🔵 start all enabled websites at startup. For each website, a **new thread** is spawned.
- 🔵 start a new website when the dispatcher asks for it (at shell command or configuration modification). When a new website is created, a **new thread** is spawned.
- 🔴 stop a running website when the dispatcher asks for it (at shell command or configuration modification). When a target website is stopped, his **website thread** is closed.

His second goal is to transmit messages from any component on the **main thread** to the related website on his **website thread**. It works like a full-duplex message route, and he can:

- transmit actions to the target website (so on the corresponding **website thread**) when the dispatcher asks for it (at **website-shell** command or **website-configuration** modification), for example when the user wants to enable a module into a specific website.
- transmit a response from a website who finished executing an action when the dispatcher asks for it (the response comes from a specific **website thread** to the **main thread**), for example when the user asks to enable a module into a specific website, the website then transmits the response to notify the user).

## Website

### WebsiteServer

### WebsiteMediator

### WebsiteModule *(implement Pizzia::IHttpModule ?)*

