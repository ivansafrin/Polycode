
#include "polybuild.h"

vector<BuildArg> args;

String getArg(String argName) {
	for(int i=0; i < args.size(); i++) {
		if(args[i].name == argName) {
			return args[i].value;
		}
	}
	return "";
}

int main(int argc, char **argv) {

	printf("Polycode build tool v0.1.0\n");

	for(int i=0; i < argc; i++) {
		String argString = String(argv[i]);
		vector<String> bits = argString.split("=");
		if(bits.size() == 2) {
			BuildArg arg;
			arg.name = bits[0];
			arg.value = bits[1];
			args.push_back(arg);
		}
		
	}
	
	if(getArg("--project") == "") {
		printf("\n\nInput project missing. Use --project=projectPath to specify.\n\n");
		return 0;
	}

	if(getArg("--out") == "") {
		printf("\n\nOutput file not specified. Use --out=outfile.poly to specify.\n\n");
		return 0;		
	}
	
	
	
	return 1;
}