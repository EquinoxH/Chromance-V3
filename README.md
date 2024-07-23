# Chromance HTTP Server API Documentation

1. [Aurora Profile Setup](#1-aurora-profile-setup)
   - [Endpoint](#endpoint)
   - [Parameters](#parameters)

2. [Blizzard Profile Setup](#2-blizzard-profile-setup)
   - [Endpoint](#endpoint-1)
   - [Parameters](#parameters-1)

3. [Clouds Profile Setup](#3-clouds-profile-setup)
   - [Endpoint](#endpoint-2)
   - [Parameters](#parameters-2)

4. [Embers Profile Setup](#4-embers-profile-setup)
   - [Endpoint](#endpoint-3)
   - [Parameters](#parameters-3)

5. [FastRGB Profile Setup](#5-fastrgb-profile-setup)
   - [Endpoint](#endpoint-4)
   - [Parameters](#parameters-4)

6. [Fireflies Profile Setup](#6-fireflies-profile-setup)
   - [Endpoint](#endpoint-5)
   - [Parameters](#parameters-5)

7. [Fireworks Profile Setup](#7-fireworks-profile-setup)
   - [Endpoint](#endpoint-6)
   - [Parameters](#parameters-6)

8. [Flower Profile Setup](#8-flower-profile-setup)
   - [Endpoint](#endpoint-7)
   - [Parameters](#parameters-7)

9. [Heart Profile Setup](#9-heart-profile-setup)
   - [Endpoint](#endpoint-8)
   - [Parameters](#parameters-8)

10. [Meteor Profile Setup](#10-meteor-profile-setup)
    - [Endpoint](#endpoint-9)
    - [Parameters](#parameters-9)

11. [MeteorStorm Profile Setup](#11-meteorstorm-profile-setup)
    - [Endpoint](#endpoint-10)
    - [Parameters](#parameters-10)

12. [Pulse Profile Setup](#12-pulse-profile-setup)
    - [Endpoint](#endpoint-11)
    - [Parameters](#parameters-11)

13. [PurpleRain Profile Setup](#13-purplerain-profile-setup)
    - [Endpoint](#endpoint-12)
    - [Parameters](#parameters-12)

14. [Rainbow Profile Setup](#14-rainbow-profile-setup)
    - [Endpoint](#endpoint-13)
    - [Parameters](#parameters-13)

15. [Rainfall Profile Setup](#15-rainfall-profile-setup)
    - [Endpoint](#endpoint-14)
    - [Parameters](#parameters-14)

16. [RGB Profile Setup](#16-rgb-profile-setup)
    - [Endpoint](#endpoint-15)
    - [Parameters](#parameters-15)

17. [Snowfall Profile Setup](#17-snowfall-profile-setup)
    - [Endpoint](#endpoint-16)
    - [Parameters](#parameters-16)

18. [Warning Profile Setup](#18-warning-profile-setup)
    - [Endpoint](#endpoint-17)
    - [Parameters](#parameters-17)

# Chromance-V3
V3 of my custom code for Voidstar's Chromance. This version is designed for the ESP32 board

## Aurora Profile Setup

This endpoint is used to configure parameters for the Aurora profile on the ESP32. The Aurora profile typically controls the behavior of LED trails, creating dynamic lighting effects.

### Endpoint

`/aurora`

### Parameters

- **numTrailsPerColour (optional):**
  - Type: Integer
  - Description: Specifies the number of LED trails to be generated for each color in the Aurora profile.
  - Example: `/aurora?numTrailsPerColour=5`

- **trailLength (optional):**
  - Type: Integer
  - Description: Sets the length of each LED trail in the Aurora profile.
  - Example: `/aurora?trailLength=20`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED trails in milliseconds.
  - Example: `/aurora?spawnDelay=50`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Controls the speed of the LED trails' movement.
  - Example: `/aurora?trailSpeed=3`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/aurora?defaults=true`
 
## Blizzard Profile Setup

This endpoint is used to configure parameters for the Blizzard profile on the ESP32. The Blizzard profile typically controls the behavior of LED flakes, creating a snowstorm-like effect.

### Endpoint

`/blizzard`

### Parameters

- **numFlakes (optional):**
  - Type: Integer
  - Description: Specifies the number of LED flakes to be generated in the Blizzard profile.
  - Example: `/blizzard?numFlakes=50`

- **speed (optional):**
  - Type: Integer
  - Description: Controls the speed of the LED flakes' movement.
  - Example: `/blizzard?speed=5`

- **trailLength (optional):**
  - Type: Integer
  - Description: Sets the length of each LED trail in the Blizzard profile.
  - Example: `/blizzard?trailLength=10`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED flakes in milliseconds.
  - Example: `/blizzard?spawnDelay=100`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/blizzard?defaults=true`

## Blizzard Profile Setup

This endpoint is used to configure parameters for the Blizzard profile on the ESP32. The Blizzard profile typically controls the behavior of LED flakes, creating a snowstorm-like effect.

### Endpoint

`/blizzard`

### Parameters

- **numFlakes (optional):**
  - Type: Integer
  - Description: Specifies the number of LED flakes to be generated in the Blizzard profile.
  - Example: `/blizzard?numFlakes=50`

- **speed (optional):**
  - Type: Integer
  - Description: Controls the speed of the LED flakes' movement.
  - Example: `/blizzard?speed=5`

- **trailLength (optional):**
  - Type: Integer
  - Description: Sets the length of each LED trail in the Blizzard profile.
  - Example: `/blizzard?trailLength=10`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED flakes in milliseconds.
  - Example: `/blizzard?spawnDelay=100`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/blizzard?defaults=true`
 
## Clouds Profile Setup

This endpoint is used to configure parameters for the Clouds profile on the ESP32. The Clouds profile typically controls the behavior of LED clouds, creating a gentle drifting effect.

### Endpoint

`/clouds`

### Parameters

- **numClouds (optional):**
  - Type: Integer
  - Description: Specifies the number of LED clouds to be generated in the Clouds profile.
  - Example: `/clouds?numClouds=3`

- **cloudLength (optional):**
  - Type: Integer
  - Description: Sets the length of each LED cloud in the Clouds profile.
  - Example: `/clouds?cloudLength=15`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED clouds in milliseconds.
  - Example: `/clouds?spawnDelay=200`

- **cloudSpeed (optional):**
  - Type: Integer
  - Description: Controls the speed of the LED clouds' movement.
  - Example: `/clouds?cloudSpeed=2`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/clouds?defaults=true`

 ## Embers Profile Setup

This endpoint is used to configure parameters for the Embers profile on the ESP32. The Embers profile typically controls the behavior of LED embers, creating a glowing and fading effect.

### Endpoint

`/embers`

### Parameters

- **numEmbers (optional):**
  - Type: Integer
  - Description: Specifies the number of LED embers to be generated in the Embers profile.
  - Example: `/embers?numEmbers=10`

- **speed (optional):**
  - Type: Integer
  - Description: Controls the speed of the LED embers' movement.
  - Example: `/embers?speed=2`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED embers in milliseconds.
  - Example: `/embers?spawnDelay=150`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/embers?defaults=true`
 
## Fast RGB Profile Setup

This endpoint is used to configure parameters for the Fast RGB profile on the ESP32. The Fast RGB profile typically controls the behavior of fast-moving LED trails with vibrant colors.

### Endpoint

`/fastRGB`

### Parameters

- **numTrails (optional):**
  - Type: Integer
  - Description: Specifies the number of fast-moving LED trails to be generated in the Fast RGB profile.
  - Example: `/fastRGB?numTrails=8`

- **trailLength (optional):**
  - Type: Integer
  - Description: Sets the length of each LED trail in the Fast RGB profile.
  - Example: `/fastRGB?trailLength=15`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED trails in milliseconds.
  - Example: `/fastRGB?spawnDelay=30`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Controls the speed of the fast-moving LED trails.
  - Example: `/fastRGB?trailSpeed=5`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/fastRGB?defaults=true`
 
## Fireflies Profile Setup

This endpoint is used to configure parameters for the Fireflies profile on the ESP32. The Fireflies profile typically controls the behavior of LED fireflies, creating a flickering and glowing effect.

### Endpoint

`/fireflies`

### Parameters

- **numFireflies (optional):**
  - Type: Integer
  - Description: Specifies the number of LED fireflies to be generated in the Fireflies profile.
  - Example: `/fireflies?numFireflies=15`

- **lifetime (optional):**
  - Type: Integer
  - Description: Sets the lifetime of each LED firefly in the Fireflies profile, controlling how long each firefly stays lit.
  - Example: `/fireflies?lifetime=100`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED fireflies in milliseconds.
  - Example: `/fireflies?spawnDelay=50`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/fireflies?defaults=true`
 
## Fireworks Profile Setup

This endpoint is used to configure parameters for the Fireworks profile on the ESP32. The Fireworks profile typically controls the behavior of LED fireworks, creating a vibrant and explosive display.

### Endpoint

`/fireworks`

### Parameters

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Defines the delay between the spawning of individual LED fireworks in milliseconds.
  - Example: `/fireworks?spawnDelay=200`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/fireworks?defaults=true`
 
## Flower Profile Setup

This endpoint is used to set up the Flower profile on the ESP32. The Flower profile typically controls the behavior of LED lights in a flower-like pattern.

### Endpoint

`/flower`

### Parameters

This endpoint does not require any specific parameters.

### Usage

- Example: `/flower`

### Note

This endpoint does not have any configurable parameters. It is used to set the profile to the predefined Flower profile.

## Heart Profile Setup

This endpoint is used to set up the Heart profile on the ESP32. The Heart profile typically controls the behavior of LED lights in a heart-shaped pattern.

### Endpoint

`/heart`

### Parameters

This endpoint does not require any specific parameters.

### Usage

- Example: `/heart`

### Note

This endpoint does not have any configurable parameters. It is used to set the profile to the predefined Heart profile.

## Meteor Profile Setup

This endpoint is used to set up the Meteor profile on the ESP32. The Meteor profile typically controls the behavior of LED lights simulating a meteor shower.

### Endpoint

`/meteor`

### Parameters

This endpoint does not require any specific parameters.

### Usage

- Example: `/meteor`

### Note

This endpoint does not have any configurable parameters. It is used to set the profile to the predefined Meteor profile.

## Meteor Storm Profile Setup

This endpoint is used to set up the Meteor Storm profile on the ESP32. The Meteor Storm profile typically controls the behavior of LED lights simulating an intense meteor shower.

### Endpoint

`/meteorStorm`

### Parameters

This endpoint does not require any specific parameters.

### Usage

- Example: `/meteorStorm`

### Note

This endpoint does not have any configurable parameters. It is used to set the profile to the predefined Meteor Storm profile.

## Pulse Profile Setup

This endpoint is used to configure parameters for the Pulse profile on the ESP32. The Pulse profile typically controls the behavior of LED lights pulsing in a dynamic pattern.

### Endpoint

`/pulse`

### Parameters

- **bigMode (optional):**
  - Type: Boolean (true/false)
  - Description: Enables or disables the big mode in the Pulse profile, altering the behavior of LED pulsing.
  - Example: `/pulse?bigMode=true`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Sets the speed of the LED trail movement in the Pulse profile.
  - Example: `/pulse?trailSpeed=5`

- **trailLength (optional):**
  - Type: Integer
  - Description: Specifies the length of the LED trail in the Pulse profile.
  - Example: `/pulse?trailLength=10`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/pulse?defaults=true`
 
## Purple Rain Profile Setup

This endpoint is used to configure parameters for the Purple Rain profile on the ESP32. The Purple Rain profile typically controls the behavior of LED lights simulating purple raindrops.

### Endpoint

`/purpleRain`

### Parameters

- **numRaindrops (optional):**
  - Type: Integer
  - Description: Sets the number of simulated raindrops in the Purple Rain profile.
  - Example: `/purpleRain?numRaindrops=50`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Sets the delay between the spawning of raindrops in the Purple Rain profile.
  - Example: `/purpleRain?spawnDelay=100`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Sets the speed of the LED trail movement in the Purple Rain profile.
  - Example: `/purpleRain?trailSpeed=5`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/purpleRain?defaults=true`
 
## Rainbow Profile Setup

This endpoint is used to set up the Rainbow profile on the ESP32. The Rainbow profile typically controls the behavior of LED lights in a dynamic and colorful rainbow pattern.

### Endpoint

`/rainbow`

### Parameters

This endpoint does not require any specific parameters.

### Usage

- Example: `/rainbow`

### Note

This endpoint does not have any configurable parameters. It is used to set the profile to the predefined Rainbow profile.

## Rainfall Profile Setup

This endpoint is used to configure parameters for the Rainfall profile on the ESP32. The Rainfall profile typically controls the behavior of LED lights simulating raindrops falling.

### Endpoint

`/rainfall`

### Parameters

- **numRaindrops (optional):**
  - Type: Integer
  - Description: Sets the number of simulated raindrops in the Rainfall profile.
  - Example: `/rainfall?numRaindrops=50`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Sets the delay between the spawning of raindrops in the Rainfall profile.
  - Example: `/rainfall?spawnDelay=100`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Sets the speed of the LED trail movement in the Rainfall profile.
  - Example: `/rainfall?trailSpeed=5`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/rainfall?defaults=true`
 
## RGB Profile Setup

This endpoint is used to configure parameters for the RGB profile on the ESP32. The RGB profile typically controls the behavior of LED lights displaying colors in various patterns.

### Endpoint

`/rgb`

### Parameters

- **numTrails (optional):**
  - Type: Integer
  - Description: Sets the number of LED trails in the RGB profile.
  - Example: `/rgb?numTrails=3`

- **trailLength (optional):**
  - Type: Integer
  - Description: Sets the length of each LED trail in the RGB profile.
  - Example: `/rgb?trailLength=10`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Sets the delay between spawning LED trails in the RGB profile.
  - Example: `/rgb?spawnDelay=50`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Sets the speed of LED trail movement in the RGB profile.
  - Example: `/rgb?trailSpeed=5`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/rgb?defaults=true`
 
## Snowfall Profile Setup

This endpoint is used to configure parameters for the Snowfall profile on the ESP32. The Snowfall profile typically controls the behavior of LED lights simulating falling snowflakes.

### Endpoint

`/snowfall`

### Parameters

- **numFlakes (optional):**
  - Type: Integer
  - Description: Sets the number of simulated snowflakes in the Snowfall profile.
  - Example: `/snowfall?numFlakes=50`

- **speed (optional):**
  - Type: Integer
  - Description: Sets the speed of snowflake movement in the Snowfall profile.
  - Example: `/snowfall?speed=3`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Sets the delay between spawning snowflakes in the Snowfall profile.
  - Example: `/snowfall?spawnDelay=100`

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/snowfall?defaults=true`
 
## Warning Profile Setup

This endpoint is used to configure parameters for the Warning profile on the ESP32. The Warning profile typically controls LED lights to convey a warning message.

### Endpoint

`/warning`

### Parameters

- **numTrails (optional):**
  - Type: Integer
  - Description: Sets the number of warning trails in the Warning profile.
  - Example: `/warning?numTrails=3`

- **trailLength (optional):**
  - Type: Integer
  - Description: Sets the length of each warning trail in the Warning profile.
  - Example: `/warning?trailLength=20`

- **spawnDelay (optional):**
  - Type: Integer
  - Description: Sets the delay between spawning warning trails in the Warning profile.
  - Example: `/warning?spawnDelay=50`

- **trailSpeed (optional):**
  - Type: Integer
  - Description: Sets the speed of movement for warning trails in the Warning profile.
  - Example: `/warning?trailSpeed=2`

- **lifetime (optional):**
  - Type: Integer
  - Description: Sets the lifetime of warning trails in the Warning profile.
  - Example: `/warning?lifetime=100`

- **colour (optional):**
  - Type: String (hex format: "RRGGBB")
  - Description: Sets the color of the warning trails in the Warning profile.
  - Example: `/warning?colour=FF0000` (sets color to red)

- **defaults (optional):**
  - Type: Boolean (true/false)
  - Description: If set to `true`, restores default values for all parameters.
  - Example: `/warning?defaults=true`
