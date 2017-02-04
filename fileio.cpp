//fileio.cpp

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <fstream>



//device: app priority timestamp data....
//void build_device_dict(ifstream& reader, ostream& os);


//app: device_name priority timestamp data....
//void write_app_i_txt(ifstream& reader, ostream& os);

using namespace std;


void write_app_i_txt(ifstream& reader, ofstream& ost, int i);

struct data 
{
  string timestamp, num_cores, cpu_req, cpu_percent, cpu_mega_hertz, mem_provisioned, mem_usage, disk_read_through, disk_write_through;
  string network_rec_through, network_trans_through;
  ofstream* ost;

  void print_data()
  {
    *ost << timestamp << " " << num_cores << " " << cpu_req  << " " << cpu_percent << " " << cpu_mega_hertz << " " << mem_provisioned;
    *ost << mem_usage << " " << disk_read_through << " " << disk_write_through  << " " << network_rec_through   << " ";
    *ost << network_trans_through << "\n";
  }

};

struct device
{
  ofstream* ost;
  string device_name, environment, location, os, os_end_date;
  data* device_data;

  device(string device_name, string environment, string location, string os, string os_end_date) : device_name(device_name), environment(environment), location(location), os(os), os_end_date(os_end_date){}

  void print_device()
  {
    *ost << device_name << " " << environment << " " << location  << " " << os << " " << os_end_date << " " ;
  }
};

struct app 
{
  string app_name, business, priority;  
  vector<device*> device_entries;
  ofstream * ost;
  int entry_count = 0;

  void print_app()
  {
    *ost << app_name << " " << business << " " << priority  << " ";
  }

};


//map<device*> device_vec;
vector<app*> app_vec;


int main(int argc, char ** argv)
{
  string prefix = "app_";
  string csv = ".csv";
  string file_name = "";
  string num = "";
  string write_to_file = "";
  string read_from_file = "";

  int num_files = atoi(argv[1]); // 100

  ifstream reader;
  filebuf fb;

  for (int i = 1; i <= num_files; ++i)
    {

      num = to_string(i);
      file_name = prefix + num;
      ofstream write_to;
      write_to_file = "txtfiles/" + file_name + ".txt";
      write_to.open(write_to_file);
      read_from_file = "csvfiles/" + file_name + csv;
   
      reader.open(read_from_file, ifstream::in);

      //write to app_i.tx
      write_app_i_txt(reader, write_to, i);

      reader.close();
      write_to.close();
    }

}




//app: device_name priority timestamp data....
void write_app_i_txt(ifstream& reader, ofstream& ost, int i)
{
  
  
  string app_name, business, priority;
  string device_name, environment, location, os, os_end_date;
  string timestamp, num_cores, cpu_req, cpu_percent, cpu_mega_hertz, mem_provisioned, mem_usage, disk_read_through, disk_write_through;
  string network_rec_through, network_trans_through;
  string junk;

  getline(reader, junk);

  while(getline(reader, device_name, ','))
    {
      app* cur_app = new app;
      app_vec.push_back(cur_app);
      //read device inf
      getline(reader, environment, ',');
      getline(reader, location, ',');
      getline(reader, os, ',');
      getline(reader, os_end_date, ',');
      
      cur_app->device_entries.push_back(new device(device_name, environment, location, os, os_end_date)); 
      cur_app->device_entries[cur_app->entry_count]->device_data = new data;
      cur_app->device_entries[cur_app->entry_count]->ost = &ost;    
      cur_app->ost = &ost;    


      //read app info
      getline(reader, cur_app->app_name, ',');
      getline(reader, cur_app->business, ',');
      getline(reader, cur_app->priority, ',');
 
      data* d_ptr = cur_app->device_entries[cur_app->entry_count]->device_data;
      d_ptr->ost = &ost;

      //read data
      getline(reader, d_ptr->num_cores, ',');
      getline(reader, d_ptr->cpu_req, ',');
      getline(reader, d_ptr->cpu_mega_hertz, ',');
      getline(reader, d_ptr->cpu_percent, ',');
      getline(reader, d_ptr->mem_provisioned, ',');
      getline(reader, d_ptr->mem_usage, ',');
      getline(reader, d_ptr->timestamp, ',');
      getline(reader, d_ptr->disk_read_through, ',');
      getline(reader, d_ptr->disk_write_through, ',');
      getline(reader, d_ptr->network_rec_through, ',');
      getline(reader, d_ptr->network_trans_through);

      cur_app->print_app();
      cur_app->device_entries[cur_app->entry_count]->print_device();
      d_ptr->print_data();
      ++cur_app->entry_count;
     
    }
  //cout << ost.str() << endl;
}
