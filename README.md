# CMD-RPG
This is an RPG game which runs in CLI.

The game has a mod system that you can use to add custom enemies and weapons.

Now Release v.1.0 !!!

(Sorry About The Bad English)


# Download Exe

Go to Assets then select version you want. Go to Build and download RPG.zip file.
Extract it to a file then double click on RPG.exe.

# Add Mods

Put the mod to the directory that consists RPG.exe file.

# Remix Project

Go to Assets then select version you want. Go to Code and download all files.
Open Visual Studio and put .h and .hpp files to Header Files.
Then put other files to Source Files.

# Make Modes

Create a .json file at the directory that consists RPG.exe file.
Open file and start editing.

# Example Code

```json
{
  "Enemys": {
    "Count": 1,
    "0": {
      "Name": "MArda",
      "Level": 5,
      "Health": 100,
      "Attack": 50,
      "Possibility": 100,
      "Crit": 50,
      "CritDamage": 75,
      "Weight": 5,
      "Speed": 40,
      "Range": 6,
      "Aggression": 2,
      "Type": 0,
      "FeaturePower": 0,
      "IsBoss": true,
      "CustomDrop": {
        "Count": 1,
        "0": {
          "Drop": "MArda's Gloves",
          "Rarity": "Mythic",
          "Weight": 100
        }
      }
    }
  },
  "Weapons": {
    "Count": 1,
    "0": {
      "Name": "MArda's Gloves",
      "Attack": 50,
      "Possibility": 100,
      "Crit": 50,
      "CritDamage": 75,
      "Speed": 40,
      "Range": 6,
      "Type": 1,
      "FeaturePower": 20,
      "Use": -1,
      "On": false,
      "HaveParentWeapon": false,
      "ParentCost": 0,
      "Cost": 0,
      "IsOnlyDrop": true
    }
  }
}
```


More will be here !
