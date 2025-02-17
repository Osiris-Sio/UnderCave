UnderCave
Autors :
	Osiris Sio (Louis AMEDRO)
	Lirei
licence CC BY SA

Features : 
	-> fights (attack/flee)
	-> potions inventory
	-> character stats
	-> many difficulties depending on the character
	-> 3 different ennemies
	-> All story
	-> Alternates endings


How to play ? -

Nothing’s easier ! Use only number and enter key of your keyboard to select and confirm an action. 
(Expect the characters name question. There you can use every key from your keyboard)



- How to launch the game on different OS (Windows/Linux) ? -


! Remarks ! :
	- Don't move out the games files. Please Don't touch the inside of the folder.
	- If you don't have a comiler/debugger C on your compter, do the first method which is the easier (based on your OS) 
		Else, we redirect you to these YouTube links if it still doesn't work :
			- Windows : https://www.youtube.com/watch?v=pTtF6TKJpo8
			- Linux (Ubuntu/Debian) : https://www.youtube.com/watch?v=5rSb1dYl_4I


Windows (2 Methods) :

	- Launch directly the game by opening the file, then execute/open the file named "UnderCave.exe"
	
	OR

	- recover the folder source path by doing a right clic on the folder, "Properties", then copy "Location" 
		(example of path : C:\Users\OSIRI\Desktop)
	- Open a command invite (CMD in the search bar)
	- Write "cd" followed by the folder location followed aswell by the folder name. Then press enter
		(exemple : cd C:\Users\OSIRI\Desktop\UnderCave)
	- Type the followed command :
		gcc main.c -o UnderCave.exe
	- Play by entering this last command : 
		.\UnderCave.exe


Linux (2 Méthodes) :

	- Open a terminal by left clicking from the game folder. 
	- Then, launch the game with the command :
		./UnderCave
	
	OR

	- Open a Terminal
	- Head to the game folder, where you've downloaded it, with the commands (or going back to the first step of the first method):
		- cd (to move from file to file) (example : cd Bureau)
		- ls (to see the files/folders where you are) (example : ls)
	- Type the Following command :
		gcc main.c -o UnderCave
	- Play by typing this command : 
		./UnderCave


- How to read the texts the right way ? -

At first, you'll find in this folder, 2 subfolders : 
    -> one having french texts (fr)
    -> one having english texts (en)

For the harder texts, for exemple : "chapter1.txt", you can find :
    -> a hard part, without spaces between lines (used for the game's code)
    -> a more lighted part, easier to read (for us humans)