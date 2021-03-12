#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// split string into vector by delimiter
std::vector<std::string> vectorize_string(char sep, std::string string_in){

    // initialize array
    std::vector<std::string> split_array;


    // initialize counters
    int start_cut = 0;
    int cut_length = 0;
    int index = 0;
    int array_index = 0;
    std::string slice;

    while (index < string_in.length()) {

        // take char and check if it is query
        char delim_query = string_in[index];

        if (delim_query == sep){
            slice = string_in.substr(start_cut, cut_length);

            // add slice to array
            split_array.push_back(slice);

            // increment counters
            start_cut = index + 1;
            cut_length = 0;
            index++;
            array_index++;
        }
        // slice the last delimited section 
        else if (index == string_in.length() - 1){
            slice = string_in.substr(start_cut, cut_length + 1);

            // add array to slice
            split_array.push_back(slice);

            // increment counters
            index++;
            array_index++;
        }
        else{
            cut_length++;
            index++;
            }
    }

    return split_array;

}

std::unordered_map<std::string, int> write_to_file(std::string umi_chrom, std::string sam_line, std::unordered_map<std::string, int> umi_chrom_dic){
    
    // if umi_chrom not is in dictionary; add to dictionary; open write to file
    if (umi_chrom_dic.find(umi_chrom) == umi_chrom_dic.end()){

        // open file
        std::ofstream sam_file(umi_chrom);

        // write to file
        sam_file << sam_line << "\n";

        // add umi to dic
        umi_chrom_dic[umi_chrom] = 0; 

        // close file
        sam_file.close();
    } 
  
    // if in dictionary; write to file
    else{
        
        // open file
        std::ofstream sam_file;
    
        // append to file
        sam_file.open(umi_chrom, std::ios_base::app);
        sam_file << sam_line << "\n";

        // close file
        sam_file.close();

    }


    return umi_chrom_dic;

}

// 
int main(int num_args, char** input_file_name){

    // variable to set each line to
    std::string sam_line;
    std::string line;
    std::vector<std::string> sam_array;
    std::vector<std::string> header_array;
    std::string umi;
    std::string chrom;
    std::string map_key;
    std::unordered_map<std::string, int> umi_chrom_dic;

    // read file with ifstream
    // INSERT PATH TO FILE HERE
    std::ifstream my_sam_file(input_file_name[1]);

    // go through file with while loop
    while (getline(my_sam_file, line)){

        // check if header line
        char check = line[0];
        char at = '@';

        if (check != at){

            // vectorize sam read
            sam_array = vectorize_string('\t', line);
            
            // vectorize header line
            header_array = vectorize_string(':', sam_array[0]);

            // umi 
            umi = header_array[7];

            // chromosome column 3
            chrom = sam_array[2];

            //separator
            char dash = '_';

            // organization key 
            map_key = umi + dash + chrom;

            // write_to_file(std::string umi_chrom, std::string sam_line, std::unordered_map<string, int> umi_chrom_dic)
            umi_chrom_dic = write_to_file(map_key, line, umi_chrom_dic);

            //std::cout << map_key << "\n";

        
        }
    
    }

    //close file
    my_sam_file.close();
}