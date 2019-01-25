# 🤖 The Zia web server architecture

## Introduction
The goal of the Zia web server is to handle multiple websites with asynchronous connections using modules to craft the response using the request.

The server aim to be fully customisable thanks to configuration files and don't need to be restarted thanks to **watcher**, and the user can interact directly with the server using shell.

<img src="https://i.imgur.com/kA7QyJR.png">

The entry point of the Zia is where all parts of the project are setup. The entry point is obviously into the **main thread**.


## Shell

At the startup of Zia, a shell that allow user to type command to interact with web server is started into **main thread**. The shell wait for data come from **stdin** asynchronously, then it send data to parser.

The parser is main part of the shell, his goal is to translate human written command into web server action.

When a command is parsed, the serialized command is **dispatched** to appropriated website (module handling) or to the **websites manager** if it's general purpose.

## Configuration watcher

At the startup of Zia, a command watcher is run into **specific watcher thread**. *(TODO: or maybe asynchronously into main thread ?)*

The command watcher wait for event come from filesystem that indicate the modification of configuration file.

When a configuration file is modified, the watcher make parsing operation into the target file  and **dispatch** new configuration data to appropriated website or to the **websites manager** if it's general purpose.

## *TODO* Dispatcher 
Need some reflection on design pattern to use for communication across all entities: **Shell**, **Configuration watcher**, **Websites manager** and all **Websites**.

We need a robust and generic way to make this communication safe and easy across all entities of the Zia web server.
A **concurrent bounded queue** with target notification system can be great and easy to use.

## Websites manager

The websites manager is the most important part of the web server. His first goal is to manage lifetime of websites:

- 🔵 start all enabled websites at startup. For each websites, a **new thread** is spawned.
- 🔵 start new website when dispatcher ask for it (at shell command or configuration modification). For new website, a **new thread** is spawned
- 🔴 stop runned website when dispatcher ask for it (at shell command or configuration modification). For the target website, his **website thread** is closed.

His second goal is to transmit messages from any component on **main thread** to related website on his **website thread**. It works like a full-duplex message route, and he can:

- transmit action to target website (so on the corresponding **website thread**) when dispatcher ask for it (at **website-shell** command or **website-configuration** modification), for example when user want to enable module into specified website.
- transmit response from a website who finished to accomplish action when dispatcher ask for it (the response come from specific **website thread** to **main thread**), for example when user ask to enable module into specified website, the website then transmit response to notify the user).

## Website

### WebsiteServer

### WebsiteMediator

### WebsiteModule *(implement Pizzia::IHttpModule ?)*

