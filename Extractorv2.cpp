#include <bits/stdc++.h>

using namespace std;

void useage();

int main(int argc, char *argv[]){
	
	if(argc!=2){
		useage();
		exit(0);
	}
	
	string itemtype;
	printf("Item type:\n>> ");
	cin>>itemtype;
	
	string category;
	printf("Category:\n>> ");
	getchar();
	getline(cin, category);
	
	// Reading file.
	
	string file_contents;
    map<int, vector<string> > csv_contents;
    char delimiter = ',';

	// Read from file to string.
	FILE* f = fopen(argv[1], "r");

	// Determine file size
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);

	char* contents = new char[size];

	rewind(f);
	fread(contents, sizeof(char), size, f);
	
	file_contents = contents;
	delete[] contents;

    istringstream sstream(file_contents);
    vector<string> items;
    string record;

    int counter = 0;
    while (getline(sstream, record)) {
        istringstream line(record);
        while (getline(line, record, delimiter)) {
        	if(record[0]=='"'){
        		string append;
				do{
					record.push_back(delimiter);
					getline(line, append, delimiter);
					record.append(append);
				}while(append[append.size()-1]!='"');
				record.erase(0,1);
				record.erase(record.size()-1,1);
			}
            items.push_back(record);
        }
        if(counter){
        	items.push_back("");
		} 
		
        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
	
	vector<string> titles = csv_contents[0];
	
	//Output!
	char filename[500];
	sprintf(filename, "Output-%ld.xml", time(NULL));
	FILE *output = fopen(filename, "wb");
	
	vector<int> desc;
	for(int i=0; i<titles.size(); i++){
		if(titles[i]=="MoE"){
			desc.push_back(i);
		}
	}
	
	fprintf(output, "<mediawiki xml:lang=\"en\">\n");
	for(int i=1; i<counter; i++){
		fprintf(output, "\t<page>\n");
		fprintf(output, "\t\t<title>%s</title>\n", csv_contents[i][0].c_str());
		fprintf(output, "\t\t<restrictions>edit=sysop:move=sysop</restrictions>\n");
		fprintf(output, "\t\t<revision>\n");
		fprintf(output, "\t\t\t<timestamp>2001-01-01T12:00:00Z</timestamp>\n");
		fprintf(output, "\t\t\t<contributor><username>MoE Generator</username></contributor>\n");
		fprintf(output, "\t\t\t<comment>Automatically generated by MoE Generator.</comment>\n");
		fprintf(output, "\t\t\t<text>&lt;onlyinclude&gt;\n");
		fprintf(output,"{{Infobox %s\n", itemtype.c_str());
		for(int j=0; j<titles.size(); j++){
			if(titles[j]!="MoE"){
				fprintf(output,"| %s = %s\n", titles[j].c_str(), csv_contents[i][j].c_str());
			}
		}
		fprintf(output, "}}\n&lt;/onlyinclude&gt;");
		if(desc.size()!=0){
			for(int j=0; j<desc.size(); j++){
				fprintf(output,"\n%s\n", csv_contents[i][desc[j]].c_str());
			}
		}
		fprintf(output, "[[Category:%s]]</text>\n", category.c_str());
		fprintf(output, "\t\t\t<minor />\n");
		fprintf(output, "\t\t</revision>\n");
		fprintf(output, "\t</page>\n");
	}
	fprintf(output, "</mediawiki>\n");
	fclose(output);
	printf("\nOutput file: %s\n", filename);
	system("PAUSE");
}

void useage(){
	printf("         MoE Generator (v0.2) - Comma\n");
	printf("** This version is for Comma-Seperated CSV files **\n");
	printf("---------------------------------------------------\n");
	printf("1. Drag your CSV file to the software.\n");
	printf("2. Enter the type of the items contained within \n");
	printf("   this file. This should be an exact match of the\n");
	printf("   name of the template (CASE SENSITIVE)\n");
	printf("3. Enter the name of the caregory, it is case sen-\n");
	printf("   sitive and should be an exact match.\n");
	printf("4. Wait until the name of the output file is shown\n");
	printf("   on the screen. This should starts with Output & \n");
	printf("   ends with XML. This file should be at the same\n");
	printf("   folder as this program.\n");
	printf("5. Upload this file to the FANDOM system, URL:\n");
	printf("   https://moe.fandom.com/wiki/Special:Import\n");
	printf("   (Just choose and upload.)\n");
	printf("6. Check it out~\n");
	printf("---------------------------------------------------\n");
	printf("Adding Description?\n");
	printf(" Set the title of a column as 'MoE' (case sensitive\n");
	printf(" and should be an exact match), and these columns \n");
	printf(" will be added to the end of the infobox in the\n");
	printf(" order adding.\n");
	printf("---------------------------------------------------\n");
	printf("This message will only present when arguments are \n");
	printf("invalid.\n");
	system("PAUSE");
}
