//Jonathan Quigley
//Worked with: Josh Sproul

void type();
void exec();
void dir();
void del();
void create();

void main(){

	int i = 0;
	int j = 0;
	int x = 0;
	int s = 0;
	char input[100];
	char cmd[4];
	char fileName[96];
	char fileName2[96];
	syscall(0, "SHELL>:");
	syscall(1, input);
	for(i = 0; i < 6; i++){
		cmd[i] = input[i];
	}
	if(cmd[0] == 't' && cmd[1] == 'y' && cmd[2] == 'p' && cmd[3] == 'e'){
		for(j = 5; j < 100; j++){
                	if(input[j] != '\0'){
                        	fileName[x] = input[j];
                       	 x++;
                	}
        	}
		type(fileName);
	}
	else if(cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] =='e' && cmd[3] == 'c'){
		for(j = 5; j < 100; j++){
                	if(input[j] != '\0'){
                        	fileName[x] = input[j];
                        	x++;
                	}
        	}

		exec(fileName);
	}
	else if(cmd[0] == 'd' && cmd[1] == 'i' && cmd[2] == 'r'){
		dir();
	}
	else if(cmd[0] == 'd' && cmd[1] == 'e' && cmd[2] == 'l'){
		for(j = 4; j < 100; j++){
                	if(input[j] != '\0'){
                        	fileName[x] = input[j];
                        	x++;
                	}
        	}

		del(fileName);
	}
	else if(cmd[0] == 'c' && cmd[1] == 'o' && cmd[2] == 'p' && cmd[3] == 'y'){
		char buffer[512];
		int sector = 0;
		for(i = 0; i<6; i++){
			if(input[i+5] == ' '){
				fileName[i] = '\0';
				break;
			}
			else{
				fileName[i] = input[i+5];
			}
		}
		fileName[6] = '\0';
		for(x = 0; x<6; x++){
			if(input[i + 6 + x] == '\0'){
				fileName2[x] = '\0';
				break;
			}
			else{
				fileName2[x] = input[i + 6 + x];
			}
		}
		fileName2[6] = '\0';
		syscall(3, fileName, buffer, &sector);
		if(sector != 0){
			syscall(8, buffer, fileName2, sector);
		}
		else{
			syscall(0, "No such file exists");
		}
	}
	else if(cmd[0] = 'c' && cmd[1] == 'r' && cmd[2] =='e' && cmd[3] =='a' && cmd[4] =='t' && cmd[5] =='e'){
		for(j = 7; j < 100; j++){
                        if(input[j] != '\0'){
                                fileName[x] = input[j];
                                x++;
                        }
                }

		create(fileName);
	}
	else{
		syscall(0, "No such command\r\n");
	}
}


void type(char* name){

	char buffer[13312];
	int sectorsRead;
	syscall(3, name, buffer, &sectorsRead);
	if(sectorsRead > 0){
		syscall(0, buffer);
	}
	else{
		syscall(0, "File Not Found");
	}
	syscall(0, "\r\n");

}

void exec(char* name){

	syscall(4, name);
	syscall(5);

}

void dir(){
	int entry = 0;
	int i = 0;
	char file[7];
	char dir[512];
	syscall(2, dir, 2);
	for(entry = 0; entry < 512; entry += 32){
		if(dir[entry] != '\0'){
			for(i = 0; i < 6; i++){
				file[i] = dir[entry + i];
			}
			file[7] = '\0';
			syscall(0, file);
			syscall(0, "\r\n");
		}
	}

}

void del(char* name){

	syscall(7, name);
	syscall(5);

}

void create(char* fileName){
	char buffer[13312];
	char input[80];
	int i;
	int x = 0;
	int sectors;
	while(input[0] != '\r'){
		i = 0;
		syscall(0, "Enter a line:");
		syscall(1, input);
		while(input[i] != 0){
			buffer[x] = input[i];
			x++;
			i++;
		}
	}
	sectors = (x+512)/512;
	syscall(8, buffer, fileName, sectors);
}
