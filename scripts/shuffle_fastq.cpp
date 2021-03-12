#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// FASTQ 'MAGIC CARD' SHUFFLE


// write out to file based on dictionary
void write_to_file(std::string out_file_name, std::string full_record){
    
    // write line out to file indicated by argument
    // open file
    std::ofstream out_file;

    // append to file
    out_file.open(out_file_name, std::ios_base::app);
    out_file << full_record << "\n";

    // close file
    out_file.close();

}

// 
int main(int num_args, char** input_file_name){

    // record variables
    std::string header;

    // full record 
    std::string full_record;
    std::string whole_record = "";

    // other variables
    std::string line;
    std::string out_file_name;
    int out_file_int = 0;
    std::string out_file_name_full;


    // read file with ifstream
    std::ifstream in_file(input_file_name[1]);

    // process first read

    // header
    getline(in_file, line);
    header = line;
    // seq
    getline(in_file, line);
    //record_array.push_back(line);
    whole_record = whole_record + "\n" + line;
    // plus
    getline(in_file, line);
    //record_array.push_back(line); 
    whole_record = whole_record + "\n" + line;
    // qual
    getline(in_file, line);
    //record_array.push_back(line);  
    whole_record = whole_record + "\n" + line;


    // go through file with while loop
    while (getline(in_file, line)){
        // increment counter
        out_file_int++;

        // reset out file name if at 100
        if (out_file_int == 100){
            out_file_int = 1;
            }

        // if header line
        char check = line[0];
        char at = '@';
        if (check == at){

            // concatanate line into whole record
            full_record = header + whole_record;
            //std::cout << full_record << "\n";

            // write out to file
            // convert int to string
            out_file_name = std::to_string(out_file_int);

            out_file_name_full = "./database/" + out_file_name + ".fastq";

            write_to_file(out_file_name_full, full_record);

            // clear record array
            whole_record = "";

            // increment file name 
            // turn string to int
            int out_file_int = stoi(out_file_name);

            // set header
            header = line;
        }
        else{
            whole_record = whole_record + "\n" + line;
        }
    
    }
    //close file
    in_file.close();

    return 0;
}