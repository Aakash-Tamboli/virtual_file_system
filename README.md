## Assignment Detail
Let'say you'r inside abcd named directory, if we type ./tmfs and PRESS ENTER

then first your application check if tmfs.fs file exists or not

step-1
if not then create a 10GB file with a data structure in first 1mb & rest will be holes.

if exists then open & load data structure

step-2
tmfs> <------ this prompt should appear on screen

step-3
the following statement should work in your virtual file system

a) if we write pwd ex: `tmfs>pwd` and press enter then [/] should appear it means you are in root

b) if we write `xcp x:/home/aakash/abcd.txt .` and press enter (x means external) then copy data of that file into our database tmfs.fs and update in data structure we are loaded

c) if we write `tmfs>ls` and press enter then should appear
	abcd.txt ---/file_size----
d) if we write `tmfs>mkdir ppp` and press enter then add entry of ppp directory in loaded data structure as well as in file DATA_STRUCTURE portition.

e) if we write `tmfs>cd ppp` and press enter this should appear
	`tmfs/ppp>`

f) if we write `tmpfs/ppp>cd ..` and press enter
	`tmfs>`

### Assignment Screenshot
![screenshot.png](https://github.com/Aakash-Tamboli/virtual_file_system/blob/master/TMAssignmentScreenshot.png)
