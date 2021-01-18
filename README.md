# Unreal4_Escape-Room-Demo

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

A simple esacpe game demo based on unreal4 game engine.

## Table of Contents

- [Background](#Background)
- [Exhibition](#Exhibition)
- [Install](#install)
- [Usage](#usage)
- [Structure](#Structure)
- [Maintainers](#Maintainers)
- [License](#license)

## Background

This is a very simple building escape game demo made by Unreal4 Game Engine.

In this demo, player needs to open two doors and escape the room. Player can use `wasd` or arrow keys to move and use mouse to change views. Additionally, player can use right mouse button to grab or release objects in the scene(button pressed to grab and button released to release).

## Exhibition

<div align="center"> <img src="https://github.com/Yunxiang-Li/Unity3D_Box-Shooter/blob/master/Screenshots%20and%20GIFs/Level1%20win.gif"/> </div>

<div align="center"> <img src="https://github.com/Yunxiang-Li/Unity3D_Box-Shooter/blob/master/Screenshots%20and%20GIFs/Level%202.PNG"/> </div>

## Install

I use Unreal4.25-4 and Visual Studio code for this project under Windows 10 environment.<br>
[Unreal download](https://www.unrealengine.com/en-US/download)<br>
[Visual Studio 2019 download](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16)<br>
[Visual Code download](https://code.visualstudio.com/docs/?dv=win)

## Usage

1. Download this repo, open(or zip and open) the **Unity3D_Box-Shooter** folder.

2. Open the **Unity Hub**, from the Home Screen, click **Projects** to view the **Projects** tab.

3. To open an existing Unity Project stored on your computer, click the Project name in the **Projects** tab, or click **Open** to browse your computer for the Project folder.

4. Note that a Unity Project is a collection of files and directories, rather than just one specific Unity Project file. To open a Project, you must select the main Project folder, rather than a specific file).

5. For this game, just select the **Unity3D_Box-Shooter** folder and open this project.

## Structure

The whole project in Unity contains two main folders, **Assets** folder and **Package** folder.

Under **Assets** folder, there are altogether **9** subfolders:

1. Animation folder: contains **3** animation for targets and one target animation controller.

2. Audio folder: contains all **5** sounds files including background music, laser, bonus hit music and so on.

3. Materials folder: contains all **8** materials need for player, targets, bumpers and so on.

4. Plugins folder: Plugins/Editor/JetBrains, creates for JetBrains Rider IDE.

5. Prefabs folder: contains all **15** prefabs I will use in this game, including Projectile(bullet), Target Negative Explosion, Player and so on.

6. Scences folder: contains **2** scenes, one for level one, the other one for level two.

7. Scripts folder: contains all **12** customized C# scripts. I also use several scripts(ContrastEnhance.cs, Bloom.cs and so on) from **Standard Assets** folder provided by Unity.

8. Standard Assets folder: provided by Unity, this will be handy and help us a lot when creating a game demo.

9. Textures folder: including textures for skybox and crosshair.

## Maintainers

[@Yunxiang-Li](https://github.com/Yunxiang-Li).

## License

[MIT license](https://github.com/Yunxiang-Li/Unreal4_Escape-Room-Demo/blob/master/LICENSE)
