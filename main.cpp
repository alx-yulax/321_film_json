#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include "nlohmann/json.hpp"

namespace Actor_json {
    struct Actor {
        std::string name;
        std::string surname;
        std::string country;
        std::tm birthday;
    };

    void to_json(nlohmann::json &j, const Actor &a) {
        char mbstr[100];
        std::strftime(mbstr, sizeof(mbstr), "%d %b %Y", &a.birthday);
        j = nlohmann::json{{"name",     a.name},
                           {"surname",  a.surname},
                           {"country",  a.country},
                           {"birthday", mbstr}};
    }
}

namespace Film_json {
    struct Film {
        std::string title;
        int year;
        int runtimeMin;
        std::string director;
        std::string cinematography;

        std::vector<std::string> productionCompanies;
        std::tm released;
        std::vector<Actor_json::Actor> actors;
    };

    void to_json(nlohmann::json &j, const Film &f) {
        j = nlohmann::json{{"title",          f.title},
                           {"year",           f.year},
                           {"runtimeMin",     f.runtimeMin},
                           {"director",       f.director},
                           {"cinematography", f.cinematography}};
        for (int i = 0; i < f.productionCompanies.size(); ++i) {
            j["productionCompanies"].push_back(f.productionCompanies[i]);
        };
        char mbstr[100];
        std::strftime(mbstr, sizeof(mbstr), "%d %b %Y", &f.released);
        j["released"] = mbstr;
        for (int i = 0; i < f.actors.size(); ++i) {
            nlohmann::json actor;
            actor = f.actors[i];
            j["actors"].push_back(actor);
        }
    }
}

int main() {
    Film_json::Film SpiderMan{"Spider-Man: No Way Home", 2021, 148, "Jon Watts", "Mauro Fiore"};
    SpiderMan.productionCompanies.push_back("Columbia Pictures");
    SpiderMan.productionCompanies.push_back("Marvel Studios");
    SpiderMan.productionCompanies.push_back("Pascal Pictures");

    std::tm released = {0, 0, 0, 17, 11, 121};
    SpiderMan.released = released;

    SpiderMan.actors.push_back(Actor_json::Actor{"Thomas", "Holland", "London, England", std::tm{0, 0, 0, 1, 5, 96}});
    SpiderMan.actors.push_back(
            Actor_json::Actor{"Zendaya", "Coleman", "Oakland, California, U.S.", std::tm{0, 0, 0, 1, 8, 96}});
    SpiderMan.actors.push_back(
            Actor_json::Actor{"Benedict", "Cumberbatch", "Hammersmith, London, England", std::tm{0, 0, 0, 19, 6,76}});

    nlohmann::json j = SpiderMan;
    std::ofstream f("film.json");
    f << j;
    f.close();

    return 0;
}
