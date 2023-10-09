# Pico-Updated
[Pico][pico] updated to latest version of GTA (1.67 Build 3028) and with some nice features.

## Some info
Original Uknowncheats post is [here][pico].
<details>
<summary>Image of Menu</summary>
<br>
<img src="https://raw.githubusercontent.com/SpaghettDev/Pico-Updated/master/assets/Pico.png" width="420"/>
</details>

<details>
<summary>How to generate the solution</summary>

If you have no experience in building a dll using Visual Studio, then you can head to the [releases](https://github.com/SpaghettDev/Pico-Updated/releases) and download the pre-built dll.
<br>
If not, then follow these steps:
1. Clone this repo (you will need the [git cli](https://git-scm.com/downloads)):
```shell
git clone https://github.com/SpaghettDev/Pico-Updated.git
```
2. cd to the folder that now contains the cloned repo:
```shell
cd path/to/cloned/repo
```
3. Make the solution (you will need the [cmake cli](https://cmake.org/download)):
```shell
mkdir build
cd build
cmake ..
```
4. The solution will be in the build folder
</details>

Was bored so decided to take on the challenge of updating a menu to work on the latest patch.

[master](https://github.com/SpaghettDev/Pico-Updated/tree/master) branch has the base with some nice features added in. </br>
[base](https://github.com/SpaghettDev/Pico-Updated/tree/base) branch has the base with no modifications, but works in the latest patch.</br>
[native-ui](https://github.com/SpaghettDev/Pico-Updated/tree/native-ui) branch has modifications that make it look like a NativeUI menu.</br>

[pico]: https://www.unknowncheats.me/forum/grand-theft-auto-v/473067-project-pico-nativeui.html
