# MVFT Aircraft Simulator

This is the main source repository for the MVFT realtime aircraft simulator for use in prototyping and pilot training. 

## Setup
To configure a CAEN machine to use the simulator in-editor, follow these instructions:
1. Use AppsAnywhere to install:
   - Visual Studio 2019 (Must be installed, but 2022 can also be installed alongside for better editing)
   - Unreal Engine __5.0.3__ 
   - Epic Games Launcher (must be installed for `XInput1_3.dll` etc, does not need to be running)
   - TortoiseGit
2. Use TortoiseGit to clone this repository (enable Depth 1 to avoid downloading the entire history) __into your Downloads folder__. This is very important, because it is not networked. If you try to open the project from your home folder, it will probably error while filling up your network quota.
    - because of this, you must commit and push all changes you make before logging out, otherwise you may lose your work.
    - ![TortoiseGit](https://user-images.githubusercontent.com/55766810/193943765-d771fc12-c610-43bd-a685-58a3091e3165.png)

### For Pilots and Users
4. Run `openeditor.bat` and `opensteamvr.bat` in the repository root folder. This will launch SteamVR (or skip if that is not installed) and Unreal. You can open SteamVR and Unreal manually by following these instructions:
    1.  Open the Simulator repository folder in Explorer and launch SteamVR by running `opensteamvr.bat`
    2. run `openeditor.bat` to launch Unreal
5. On first-time launch, Unreal should ask to compile content, press Yes, then that should complete and the editor window should appear.
    - Wait for shaders to finish compiling for visuals to be correct
    - It will take around 20 minutes for Unreal to first-time launch on a CAEN computer, so if it looks stuck, it's not, just give it some time (subsequent launches on the same machine will be much faster)
6. To run in VR, select the dropdown menu next to Play, and select VR Preview. SteamVR needs to be running (and have been launched before Unreal). It will launch a separate window. To exit, press the escape key or alt-tab to the Unreal window.
    
### For Developers
4. Run `genvs.bat` in the repository root folder. This will generate a Visual Studio solution file.
5. Open the generated `PTrain.sln` in the repository root folder.
6. In the solution explorer, right-click PTrain and select "Set as Startup Project"
7. In the top toolbar, select `DebugGame Editor`
8. Press the green play button labeled Local Windows Debugger. This will compile the project and launch Unreal.

To configure on a personal computer:
1. Install prerequisites for your platform:
    - All: 
        - SteamVR (optional) (for VR support, note SteamVR does not support macOS)
        - [git-lfs](https://git-lfs.github.com/) (required for binary file locking)
        - Unreal Engine __5.0.3__.
    - macOS: Xcode
    - Windows: Visual Studio with Desktop Development for C++ module
3. Clone using `git clone --depth=1`. If you did not install git-lfs, this will not work. 
4. Open `PTrain.uproject`. When prompted to compile content, press Yes, and wait for that to complete. After that, the Editor window should appear. It should auto-launch SteamVR. If it does not, you must close Unreal, launch SteamVR manually, and then reopen Unreal. 

## Pushing your changes
Make sure to work on a branch for each feature.
1. `git checkout -b your-feature-name`
2. Make your changes
3. `git status`, read the output and use `git add <filename>` to include files 
4. `git commit -m "explain your changes here"`
5. `git push origin your-feature-name`
6. Visit this page while logged in, you should see a `Compare & Pull Request` button, press it and fill out the form
7. The Avionics lead will merge your changes

## Writing C++ code
1. Right-click `PTrain.uproject` and select Generate Xcode/Visual Studio Project
    - If this option is not available, open `PTrain.uproject` and go to File->Generate Xcode/Visual Studio Project
    - Afterwards, close the editor
2. Open the generated IDE project file and press the Start Debugging (Visual Studio) or Run (Xcode) button
    - This will launch the Editor with the debugger attached so C++ source debugging works
    - You can also use Attach To Process on an already-running Editor from your IDE to debug from there without restarting it
3. Commit your changes and submit pull requests as normal.

## Editing binary files, or non-mergeable files (`.uasset`, `.umap`, `.fbx`, `.png`, `.ma`, `.mb`,  etc)
1. In Explorer, right-click the file you want to work on and press `TortoiseGit -> LFS -> Lock File`. __This is very important!!__ It will ensure nobody else edits that file and that you will be able to merge your changes correctly.
   - ![tortoise LFS](https://user-images.githubusercontent.com/55766810/195214057-9a4a9792-2e33-448a-ad52-242810801578.png)
2. Make your changes to the file
3. Commit & submit PR as usual
4. When the PR is merged, use TortoiseGit to unlock the file. 

More information about file locking is available here: https://tortoisegit.org/docs/tortoisegit/tgit-dug-lfslocking.html

## 3D Models
We use Autodesk Maya for all model creation for use in the simulator. You can install Maya from AppsAnywhere when logged in to CAEN. You may optionally acquire a free student license for Maya from Autodesk
by providing a photo of your student ID when creating an educational account. 

### Modeling notes:
1. Save model files as **.ma** into the `Models` directory.
2. Export FBX files from maya into the `Models/exports` directory.
3. Ensure your Maya scene dimension is set to Centimeters (the default) or Meters.
4. Ensure transformations for your root object are frozen before export.
5. To import your FBX into unreal, drag the files from the file explorer to the `Content/Assets` directory. Then apply the following settings:
   - Generate Missing Collision: **false**
   - Material Import Method: **Do not Create Material**
   - Import Textures: **false**
6. To update your model in unreal after exporting a new version, right click the model in Assets and press Reimport.

## Importing Data
We use CSV files for data-driven parts of the simulator. An example CSV file is provided below:
```
Name,0,500,1000,2000,6000
Prop.ThrustByRPM,0,30,40,60,100
```
The row is (name, x-values). The values afterward are the Y-values. All rows share X values.

Once your CSV file has been created, drag it into the `DataB`P folder in the Unreal Editor and set the dialog properties like so:

![CSV import settings](https://user-images.githubusercontent.com/55766810/229934963-62684739-73bf-417a-b793-f5064777fe95.png)

Once imported, open the blueprint and the data should be visible.

![Data blueprint preview](https://user-images.githubusercontent.com/55766810/229935025-690ce646-6f69-4faa-bf8f-640877978767.png)

The imported blueprint will not automatically update to reflect changes made to the CSV. To manually resync, Right click -> Reimport.

## Usage In Editor
- The `Arena20XX` Level files contains the simulated environments. Press Play to start the simulation

## Generating Builds
For CAEN (recommended)
- Run `build.bat`.The built program will be written to the parent directory (not in the repository folder) named WindowsNoEditor. You might need to bake lighting in-editor first in order for the result to look correct. 

For other platforms
- Go to File->Package Project, and select the desired target. 
