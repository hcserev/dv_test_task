#include "DaVinci_DataStruct.h"

int main()
{
    std::string filePath;
    std::cout << "enter file path" << std::endl;
    std::getline(std::cin, filePath);
    DaVinci::DataStruct* data = new DaVinci::DataStruct(filePath);
    //DaVinci::DataStruct* data = new DaVinci::DataStruct("E:/orders coding test developer.dat");

    // test cases
    auto m = data->OrderCounts();
    auto a = data->BiggestBuyOrders("DVAM2");
    auto p = data->BestSellAtTime("DVAM1", "15:14:00");

    std::cout << "price = " << p.first << "; volume = " << p.second << std::endl;
}
