#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#define SIZE 1000


void killprocess() 
{ 
	int pid; 
	
	system("ps"); 
	pid = getpid(); 
	printf("-----------------------------------------------------------------\n"); 
	printf("killprocess() was called.  Kill pid = %d\n", pid); 
	printf("-----------------------------------------------------------------\n"); 
	fflush(stdout); 
	kill(pid, SIGKILL); 
	exit(10); 								 
} 
 


int main(void) {
	signal(SIGALRM, killprocess);
	//print system calls 
	//display your user id use getuid()
	//Display your group id by using getgid().
	//Display the host you are on using gethostname(). 
	//Display the domain name of your host using getdomainname(). 
	//Display your current working directory using getcwd().

	char hostbuffer[256];
	char group[256];
	struct stat passStat;
	struct sysinfo info;
    	int host_entry;
    	int hostname;
  
    	// To retrieve hostname
   	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
  
	printf("The real user ID is %d\n", getuid());
    	printf("Hostname: %s\n", hostbuffer);	
	printf("The group user is %d\n", getgid());
	getdomainname(hostbuffer, sizeof(hostbuffer));
	printf("Group Domain name is %s\n", hostbuffer);

	getcwd(hostbuffer, sizeof(hostbuffer));
	printf("Displays the working directory is %s\n", hostbuffer);

	if ( access("/etc/passwd", F_OK) != -1){
		printf("/etc/passwd exists");		
	}
	if (access("/etc/passwd", R_OK) != -1){
		printf("/etc/passwd is able to be read");
	}
	if (access("/etc/passwd", W_OK) != -1){
		printf("/etc/passwd is able to be written");
	}

	system("id; hostname; domainname; pwd; cat /etc/passwd | grep kadejha");

	stat("/etc/passwd", &passStat);

	system("ls -l /etc/passwd");

	
	if(access("demo.dir", F_OK) != -1){
		printf("demo.dir exists.");
	}else{
		mkdir("demo.dir", 0755);
	}
	chdir("demo.dir");

	getcwd(hostbuffer, sizeof(hostbuffer));
	printf("Displays the working directory is %s\n", hostbuffer);

	printf("printing out the process id: %d\n", getpid());
	printf("printing out the parent process id: %d\n", getppid());	

	system("ps -ef > processes.txt; cat processes.txt");

	sysinfo(&info);
	printf("in seconds: %ld\n", info.uptime);
	printf("in min: %ld\n", info.uptime / 60);
	printf("in hours: %ld\n", info.uptime / 360);
	printf("in days: %ld\n", info.uptime / 8640);

	//finding load avg
	
	printf("load avg 1: %lu\n", info.loads[0]);
	printf("load avg 5: %lu\n", info.loads[1]);
	printf("load avg 15: %lu\n", info.loads[2]);

	printf("free Ram: %lu\n", info.freeram);
	printf("Total Ram: %lu\n", info.totalram);
	printf("Proceeses running: %u\n", info.procs);
	
	 int forNum = fork();

	if(forNum == 0){

		printf("Child process \n");
		printf("Child process id = %d\n", getpid());
		printf("Child’s parent process id =  %d\n", getppid());
		printf("---------------------------------------------------------\n");
		system("ps -ef\n");
		printf("---------------------------------------------------------\n");

		alarm(10);
	}else{
		printf("Parent Process \n");
		printf("Parent process id = %d\n", getpid());
		printf("Parent's parent process id =  %d\n", getppid());

		alarm(5);
	}
	
	sleep(60);
	printf("ALL DONE!");
	

	return 0;	
};

