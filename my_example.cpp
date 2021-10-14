#include <cstdio>	//stdandard output
#include <cstdlib>

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>
#include <SoapySDR/Formats.hpp>

#include <string>	// std::string
#include <vector>	// std::vector<...>
#include <map>		// std::map< ... , ... >

#include <iostream>
using namespace std;
using namespace SoapySDR;

vector<string> temp_list;
int main()
{
	
	// 1. enumerate devices (list all devices' information)
	KwargsList results = Device::enumerate();
	cout << "############################\n";
	for(int i = 0; i < results.size(); i++)
	{
		cout << "Found dcevice #" << i << '\n';
		for(auto it = results[i].begin(); it != results[i].end(); it++) {
			cout << it->first << "=" << it->second << '\n';
		}
	}
	cout << "############################\n";
	
	// 2. make device
	Kwargs args = results[0];
	Device *sdr = Device::make(args);

	// 3. listing antennas
	temp_list = sdr->listAntennas(SOAPY_SDR_RX, 0);
	cout << "Rx antennas : ";
	cout << temp_list[0];
	for (int i=1; i<temp_list.size(); i++) {
		cout << ", " <<temp_list[i];
	}
	cout << "\n############################\n";
	
	// 4. set antenna & get the antenna
	sdr->setAntenna(SOAPY_SDR_RX, 0, "LNAW");
	string antenna_name = sdr->getAntenna(SOAPY_SDR_RX, 0);
	cout << "antenna_name is : " << antenna_name << '\n';
	
	cout << "\n############################\n";
	
	// 5. getNumChannels
	int numChannel = sdr->getNumChannels(SOAPY_SDR_RX);
	cout << "numChannel is : "<< numChannel << '\n';
	
	// 0. unmake device
	Device::unmake( sdr );
	cout << "END\n";
	cout << "\n############################\n";
	
	temp_list.clear();
	return EXIT_SUCCESS;
}
