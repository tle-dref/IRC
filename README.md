# 💬 Ft_IRC  
### 🚀 Serveur IRC conforme à la RFC 1459  

## 📌 Description  
Ft_IRC est une implémentation d'un **serveur IRC** conforme à la **RFC 1459**.  
Il permet aux clients de se connecter, de créer et gérer des **canaux**, d'envoyer des **messages privés**, et de gérer les **permissions des utilisateurs**.  

Ce projet a été réalisé dans le cadre de l'École 42 pour comprendre les **protocoles réseau**, la **gestion des connexions**, et le **développement serveur en C**.  

## 🔧 Fonctionnalités  
✔️ Connexion et authentification des utilisateurs 🔑  
✔️ Création et gestion des **canaux** (`JOIN`, `PART`, `KICK`, `TOPIC`, `MODE`...)  
✔️ Envoi de **messages privés** et **messages de groupe** (`PRIVMSG`, `NOTICE`)  
✔️ Gestion des **permissions** (opérateurs, bans, restrictions)  
✔️ Respect du **protocole IRC (RFC 1459)** 📜  
✔️ Communication via **sockets TCP**  

## 🏗️ Installation et Compilation  

### 📥 Cloner le projet  
```sh
git clone https://github.com/tle-dref/ft_irc.git
cd ft_irc
🔨 Compiler
sh
Copier
Modifier
make
```
🚀 Lancer le serveur IRC
```sh
./ircserv <port> <password>
```
port : Port d’écoute du serveur (ex: 6667)
password : Mot de passe pour se connecter au serveur
💻 Se connecter avec un client IRC
Tu peux utiliser un client IRC comme WeeChat, HexChat, irssi, ou Netcat :
```sh
nc 127.0.0.1 6667
```
⚙️ Technologies utilisées
🟢 Langage : Cpp++98
🔌 Sockets : TCP/IP
📡 Protocoles : IRC (RFC 1459)

📜 RFC 1459 - Références
RFC 1459 - Internet Relay Chat Protocol
