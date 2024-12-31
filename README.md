<p float="center">
    <img src="https://github.com/XargonWan/RetroQUEST/blob/main/res/RetroQUEST_Logo.png?raw=true" alt="RetroQUEST logo" width="600"/>
</p>

# RetroQUEST

> [!IMPORTANT]
> NOTE: RetroQUEST is a mere techincal preview now, the following description is the actual project scope and not what is actually implemented.
> Assets are just placeholders and not final, every asset you see now will be discarded and redone.
> This repo is pretty much a dump, I will clean it up later, sorry.

**RetroQUEST** is an immersive gaming experience that takes you through the history of video game consoles, from the earliest systems to the dawn of the 21st century. Designed in **GODOT 4.3** primarily for **Meta Quest 3**, it is also fully playable on **Linux** in a non-VR mode. RetroQUEST is a standalone application, providing a unique way to explore gaming history, manage consoles, and enjoy retro games as a Story Mode is available along a Sandbox Mode. 

## Features

### Explore Gaming History
- Start your journey in the 1970s with the first home consoles, and progress through over 30 years of gaming milestones, concluding with the **PlayStation Portable** and beyond.
- Experience the evolution of video game technology through immersive interactions and era-specific challenges.

### Console and Game Management
- Collect and manage consoles from various generations, configuring them to play your favorite games.
- Load your personal **ROMs** and **BIOS files** (not included) to emulate classic games natively within the app.
- Showcase your collection in an interactive and customizable environment.

### Dynamic Game World
- The passage of time within the game mirrors the progression of gaming eras, moving faster than real-world time to simulate decades of advancements.
- Revisit significant historical moments to replay key experiences.

### Customization and Collectibles
- Personalize your gaming room with era-specific furniture, decorations, and interactive items.
- Collect gaming memorabilia, including magazines, peripherals, and recordings of pivotal moments in gaming history.

### Era-Based Gameplay
- Each era introduces unique gameplay mechanics, challenges, and unlockable content.
- Progress through a structured timeline or replay specific key moments to explore new possibilities.

### Free and Open Source
- RetroQUEST is **Free and Open Source Software (FOSS)**, fostering a community-driven development model.
- The app does not include ROMs, BIOS files, or in-game purchases, ensuring compliance with legal and ethical standards.

## Game Modes

### Story Mode
- A campaign spanning over 32 in-game years, guiding players through the golden age of gaming history.
- Revisit specific key points in the timeline to refine your strategy or relive iconic moments.
- Earn credits in game and use them to buy and collect new consoles or games when they are released.
- Hence no specific games are mandatory to play the sotry mode there will be a list of suggested iconic games to fully enjoy the story. These games will unlock more story contents.

### **Sandbox Mode**
- Play in a sandbox mode where every game and consoles are free and out of the time: experimenting with setups, collections, or focusing on retro gameplay.
- Perfect for players who prefer a more relaxed and open-ended experience or they just want to use the application as a VR emulation frontend.

## **Platform Compatibility**

RetroQUEST is designed primarily for **VR** on **Meta Quest 3**, offering a standalone experience that doesn’t require a PC. However, it is also fully playable in **non-VR mode** on **Linux**, making it accessible to a broader audience.
We aim to add support to other VR headsets and OSs as Windows and Mac.

# RetroQUEST is looking for more!

### **Join the RetroQUEST Development Team!**  

**RetroQUEST** is a unique, open-source project that reimagines the history of gaming in an interactive and immersive way. Designed **primarily for native VR** on **Meta Quest 3** and also playable on **Linux**, with plans to expand to **Windows** and **Mac**, RetroQUEST aims to provide an experience unlike anything else currently available for native VR.  

This is not a PCVR experience but a fully **native VR** project that lets players explore and interact with decades of gaming history while also supporting traditional non-VR gameplay for broader accessibility.  

### **We’re Looking for Collaborators**  

We need passionate individuals to help the development of RetroQUEST, here’s where we could use your expertise:  

- **C++ Developers (Libretro Integration)**: Help enhance and integrate gdlibretro library cores to emulate gaming systems within the RetroQUEST environment.  
- **Godot Developers (VR and Non-VR)**: Create core gameplay mechanics, immersive VR interactions, and user-friendly non-VR experiences.  
- **Sound and Music Designers**: Develop soundtracks and effects that capture the spirit of gaming’s different eras.  
- **3D Modelers and Animators**: Design and animate detailed, stylized consoles, controllers, characters and environments.

# Development notes

## Compiling gdlibretro
RetroQUEST uses a customized version of the [gdlibretro](https://github.com/gabrielmedici/gdlibretro) godot library (writtein in C++) to load libretro cores in Godot directly.
The project provides the library already compiled and even the sources in case the end user wants to edit and compile its own version.

In order to do so just run:
```
./build_gdlibretro.sh
```

## How to test RetroQUEST on PC
- create a `roms` and `cores` folder in the root of the project
- Place a game in the roms folder, for example now the path `roms/megadrive/Sonic the Hedgehog.bin` is hardcoded, if you want another one you must change the variable.
- Same logic for the core, now hardcoded `cores/genesis_plus_gx_libretro.so`.
- Open the project with Godot 4.3 and run it.

## How to test RetroQUEST on Meta Quest 3
TBD

## FAQ

### Can I play RetroQUEST now?  
At the moment, RetroQUEST is in a pre-alpha state. Emulation is not functional yet. You can explore a placeholder bedroom environment, and if you're familiar with Godot, you can load the project and test its current features. 

### Here in the FAQ I can see a lot of features, where are they?  
The features mentioned in the FAQ are part of our vision for RetroQUEST. They will be implemented gradually over time as the project evolves. Stay tuned for updates and feel free to contribute if you want to see a specific feature sooner!

### What happens if I don't have the suggested games in my library?  
In Story Mode, these games will appear in the storyline but will be marked as sold-out when viewed in the in-game catalog. The story will proceed without requiring you to have these games.  

### Until which system can I play?  
You can play any system supported by RetroArch that is compatible with the Meta Quest hardware, up to the PlayStation Portable (PSP).  
On PC, PCVR, or other platforms, this limitation may be removed in future updates.  

### Can I play standalone emulators such as Dolphin or Duckstation?  
Currently, we don't plan to support standalone emulators due to technical challenges.  
However, contributions are welcome if you know how to integrate them!  

### What is the difference between Story Mode and Sandbox? Am I forced to play the Story Mode to unlock Sandbox?  
- **Story Mode**: Experience the evolution of gaming, unlocking systems and games progressively by advancing through the storyline. Systems and games are acquired via an in-game catalog using currency earned in-game.  
- **Sandbox Mode**: All systems are unlocked from the start, allowing you to explore "out of timeline" gameplay freely.  
  While everything is unlocked in Sandbox, Story Mode progress may unlock unique furniture or graphical customizations.  

### About in-game currency  
#### Do I need to buy in-game currency with real money?  
No. You earn in-game currency purely through gameplay. RetroQUEST is free and open source. If you'd like to support the project, you can donate, but donations don't provide in-game benefits.  

### Do I need to own the games before acquiring them via the catalog?  
Yes. The catalog will display games you’ve placed in your ROMs folder, along with some story-related games. If a game is not in your folder, it won’t be available in the catalog.  

### Why the name RetroQUEST if the game is multi-platform?  
The name **RetroQUEST** reflects the core gaming experience on Meta Quest 3, which is the primary VR device used in development. "QUEST" also symbolizes the player's journey through the history of gaming. This differentiates RetroQUEST from other emulation frontends, emphasizing its narrative-driven Story Mode.  

### What can I do if I don't own any games or old consoles?  
Unfortunately, RetroQUEST is designed to enhance the experience of retro game emulation, so you'll need to provide your own games. This could be a great opportunity to start collecting retro titles! Check local thrift stores or legal sources for retro games.  

### Is the Story Mode aimed to deliver a didactic experience?  
Yes, partially. While the storyline stays as true to gaming history as possible, any fictional elements will be clearly marked to ensure users are aware of historical deviations. The goal is to provide an engaging and educational experience for gamers of all backgrounds.

### I developed a retro game that can be emulated. Can I ship it with RetroQUEST?  
Please get in touch! We’d love to discuss this possibility. However, keep in mind that RetroQUEST operates without any monetary transactions. By including your game, you would be distributing it for free and under the terms of RetroQUEST's license.

### Can I use the TV to play VHS?  
Kind of, yes! We plan to add a feature that allows you to play or stream custom video files on the in-game TV.  

### What about the radio or walkman?  
Similarly, we aim to support audio files or streams for the in-game radio and walkman.

### Where is my inventory and options menu?  
We aim to minimize reliance on traditional menus by integrating features directly into the game environment. Here's how some key functions are handled:  

- **Inventory**: Your room's chest acts as your inventory, storing items like cartridges, systems, consoles, and furniture that can be placed in the environment.  
- **Music Controls**: The radio doubles as the music volume control and play/mute toggle.  
- **Subtitles**: The TV remote can be used to turn subtitles on or off.  
- **Shop**: The in-game shop is represented by magazines delivered to your door.  
- **Lighting**: Room lights can be controlled with a remote or the in-room switch.  
- **Saving**: The bed is used for sleeping (to skip the day) or quick saving manually (taking a nap).  
- **Quitting to Menu**: Opening and crossing the door saves the game and exits to the main menu.  
- **Game Genie Cartridge**: Plug this into any console for advanced features like enabling cheats, toggling quick resume (save and load states), accessing Retro Achievements, fast forward, and toggling BIOS loading.

### Can I change screen shaders?  
Each TV in RetroQUEST comes with its own unique shader, emulating the look and feel of the original hardware. Changing the TV will also change the shader.  

Additionally:  
- **Modern TVs**: A modern TV is available with no shader and upscaling for a clean display.  
- **Handheld Consoles**: Handheld systems include their "modified" versions featuring aftermarket shells and LCD screens for improved clarity and aesthetics.
