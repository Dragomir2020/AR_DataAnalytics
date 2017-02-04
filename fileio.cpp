//fileio.cpp

#include <ostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "device.h"
#include "app.h"



//device: app priority timestamp data....
void build_device_dict(ifstream& reader, ostream& os);


//app: device_name priority timestamp data....
void write_app_i_txt(ifstream& reader, ostream& os);



struct data 
{
  std::string timestamp, num_cores, cpu_req, cpu_percent, cpu_mega_hertz, mem_provisioned, mem_usage, disk_read_through, disk_write_through;
  std::string network_rec_through, network_trans_through;

  void print_data()
  {
    std::cout << timestamp << " " << num_cores << " " << cpu_req  << " " << cpu_percent << " " << cpu_mega_hertz << " " << mem_provisioned;
    std::cout << mem_usage << " " << disk_read_through << " " << disk_write_through  << " " << network_rec_through   << " ";
    std::cout << network_trans_through << "\n";
  }

};

struct device
{
  std::string device_name, environment, location, os, os_end_date;
  data* device_data;

  void print_device()
  {
    std::cout << device_name << " " << environment << " " << location  << " " << os << " " << os_end_date << " " ;
  }
};

struct app 
{
  std::string app_name, business, priority;  
  std::vector<device*> devices_for_app;;
  int entry_count = 0;

  void print_app()
  {
    std::cout << app_name << " " << environment << " " << location  << " " << os << " " ;
  }

};


std::map<device*> device_vec;
std::vector<app*> app_vec;


int main(int argc, char ** argv)
{
  string prefix = "app_";
  string csv = ".csv";
  string file_name = "";

  int num_files = argv[1]; // 100

  ifstream reader;


  for (int i = 0; i < num_files; ++i)
    {
      file_name = prefix + itoa(i);
      ostream ost;

      reader.open(file_name + csv);
      
      //write to app_i.tx
      write_app_i_txt(reader, ost, filename);

      reader.close();
    }

}




//app: device_name priority timestamp data....
void write_app_i_txt(ifstream& reader, ostream& ost, int i)
{
  
  
  string app_name, business, priority;
  string device_name, environment, location, os, os_end_date;
  string timestamp, num_cores, cpu_req, cpu_percent, cpu_mega_hertz, mem_provisioned, mem_usage, disk_read_through, disk_write_through;
  string network_rec_through, network_trans_through;

  
  
  while(getline(reader, device_name, ','))
    {
      app* cur_app = new app;
      app_vec.push_pack(cur_app);
 
      //read device inf
      getline(reader, device_name, ',');
      getline(reader, environment, ',');
      getline(reader, location, ',');
      getline(reader, os, ',');
      getline(reader, os_end_date, ',');
      
      cur_app->device_entries.push_back(new device(device_name, environment, location, os, os_end_date));     
      
      //read app info
      getline(reader, cur_app->app_name, ',');
      getline(reader, cur_app->business ',');
      getline(reader, cur_app->priority, ',');
 
      data* d_ptr = cur_app->device_entries[cur_app.entry_count]->device_data;

      //read data
      getline(reader, d_ptr->num_cpus, ',');
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

      cur_app.print_app();
      cur_app.device_entries[cur_app.entry_count].print_device();
      d_ptr->print_data();
      ++cur_app.entry_count;
     
    }
  
}
