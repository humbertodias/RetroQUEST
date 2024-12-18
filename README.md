<p float="center">
    <img src="https://github.com/XargonWan/RetroQUEST/blob/gdlibretro/res/RetroQUEST_Logo.png?raw=true" alt="RetroQUEST logo" width="600"/>
</p>

# RetroQUEST

> [!IMPORTANT]
> NOTE: RetroQUEST is a mere techincal preview now, the following description is the actual project scope and not what is actually implemented.
> Assets are just placeholders and not final, every asset you see now will be discarded and redone.

**RetroQUEST** is an immersive gaming experience that takes you through the history of video game consoles, from the earliest systems to the dawn of the 21st century. Designed in **GODOT 4.3** primarily for **Meta Quest 3**, it is also fully playable on **Linux** in a non-VR mode. RetroQUEST is a standalone application, providing a unique way to explore gaming history, manage consoles, and enjoy retro games.

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
Open the project with Godot 4.3 and run it from there

## How to test RetroQUEST on Meta Quest 3
TBD