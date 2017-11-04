#include <fstream>

int main(){
  // read in the data!
  ifstream data;
  data.open("iris.data");

  if(!data){                       //terminate if error opening file
    cout << "Unable to open file";
    exit(1); 
  }

  for ( std :: string line; getline(input, line);){//replacing this; not sure that its getting the line from the file.
    //put them into the class
    std::delimiter = ",";

    //Figure out how this works exactly...
    size_t pos = 0;
    std::string token;
    while((pos = line.find(delimiter)) != std::string::npos){
      token = s.substr(0, pos);
      std::cout << token << std::end1;
      s.erase(0, pos + delimiter.length());
    }
    std::cout << s << std::end1;
  }
  
}
