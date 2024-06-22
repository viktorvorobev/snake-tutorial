[![CI Checks](https://github.com/viktorvorobev/snake-tutorial/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/viktorvorobev/snake-tutorial/actions/workflows/cmake-multi-platform.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![linkedin](https://img.shields.io/badge/LinkedIn-0077B5?&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mr-viktor-vorobev/)
[![](https://img.shields.io/badge/My%20CV-00A98F?logo=googledrive&logoColor=white)](https://drive.google.com/file/d/1e45Z14JU7wt4H0zuaQfNd0Xz4Yu0q1h-/view?usp=share_link)


# Snake game

Playing around with code from [this tutorial](https://youtu.be/LGqsnM_WEK4?si=prTpLXu1iOF80don)

## Building

1. Clone the repo
2. Prepare to build  
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   ```
3. Go to build directory
   ```bash
   cd build
   ```
4. Compile:
   ```bash
   make
   ```
5. Run the game:
   ```bash
   ./snake-game
   ```

<details>

<summary>Demo</summary>

![demo.gif](https://github.com/viktorvorobev/snake-tutorial/blob/main/static/demo.gif)

</details>
