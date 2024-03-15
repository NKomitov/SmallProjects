#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

const int amountOfDishes = 3;

std::string GetName(const std::string &str, int index);
std::string GetMeal();
bool CheckRestaurant(const std::string &restaurant, const std::string *maj, const std::string *jena, const int &len);
void GetRestaurantMatches(std::ifstream &file, const std::string *maj, const std::string *jena, const int &len, int &liked);

int main() {
  std::ifstream infile;
  infile.open("RestaurantsDatabase.txt", std::ios::out);
  if (!infile.is_open()) {
    std::cout << "No Database Found!";
    system("pause");
    return 0;
  }
  
  std::string XYhromozoma[amountOfDishes];
  std::string XXhromozoma[amountOfDishes];   //zashtoto sme sorosov universitet
  for (int i = 0; i < amountOfDishes; i++) {
    std::cout << "Write the meals for the gent: ";
    XYhromozoma[i] = GetMeal();
  }
  for (int i = 0; i < amountOfDishes; i++) {
    std::cout << "Write the meals for the lady: ";
    XXhromozoma[i] = GetMeal();
  }
  int likedRestaurantsAmount = 0;
  GetRestaurantMatches(infile, XYhromozoma, XXhromozoma, amountOfDishes, likedRestaurantsAmount);
  std::cout << "Restaurant matches: " << likedRestaurantsAmount << '\n';
  if (likedRestaurantsAmount == 0)
    std::cout << "Opa mai shte gledame ergena :((" <<'\n';
  else
    std::cout << "Sled vecherqta shte onadim :))" << '\n';
  infile.close();
  
  system("pause");
  return 0;
}

std::string GetName(const std::string &str, int index) {
  std::string output = "";
  while (str[index] != ',' && str[index] != '\n' && str[index] != 0 && str[index] != ':') {
    output += str[index];
    index++;
  }
  return output;
}

std::string GetMeal() {
  std::string meal;
  std::cin >> meal;
  if (meal[0] >= 'a' || meal[0] <= 'z')
    meal[0] -= 'a'-'A';
  return meal;
}

bool CheckRestaurant(const std::string &restaurant, const std::string *maj, const std::string *jena, const int &len) {
  std::string restaurantName = GetName(restaurant, 0);
  std::vector<std::string> qstiq;
  int jenaLikes = 0;
  bool majLikes = false;
  for (int index = 0; index < restaurant.size(); index++) {
    if (restaurant[index] == ':' || restaurant[index] == ',') {
      index++;
      for (int j = 0; j < len; j++) {
        if (maj[j] == GetName(restaurant, index)) {
          majLikes = true;
        }
        if (jena[j] == GetName(restaurant, index)) {
          jenaLikes++;
        }
        qstiq.push_back(GetName(restaurant, index));
      }
    }
  }
  auto uniq = std::unique(qstiq.begin(), qstiq.end());
  qstiq.erase(uniq, qstiq.end());
  if (majLikes && jenaLikes >= 2) {
    std::cout << "Meal matches: " << qstiq.size() << '\n';
    std::cout << "Restaurant: " << restaurantName <<'\n';
    std::cout << "The rest of the menu:" << '\n';
    for (auto i : qstiq)
      std::cout << i << '\n';
    return 1;
  }
  return 0;
}

void GetRestaurantMatches(std::ifstream &file, const std::string *maj, const std::string *jena, const int &len, int &liked) {
  std::string output = "";
  while (getline(file, output)) {
    liked += (int)CheckRestaurant(output, maj, jena, len);
  }
}