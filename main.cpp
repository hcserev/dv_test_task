#include "data_struct.h"

int main()
{
    std::string filePath;
    std::cout << "enter file path" << std::endl;
    std::getline(std::cin, filePath);
    DaVinci::DataStruct data(filePath);

    // examples
    //auto oc = data.OrderCounts();
    //auto bbo = data.BiggestBuyOrders("DVAM1");
    //auto bsat = data.BestSellAtTime("DVAM1", "12:00:01");

}
