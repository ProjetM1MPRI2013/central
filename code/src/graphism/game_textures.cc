/**
 * @author MrKulu, Adrien H.
 */


#include "game_textures.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#define DEBUG false
#include "debug.h"

namespace textures {

  std::vector<TexturePack> texVector;

  TexturePack* get(int n) {
    return(&(texVector.at(n)));
  }

  void initialize() {

    std::fstream file;
    file.open("../graphism/animations",std::fstream::in);
    assert(file);
    std::string line, tmp;
    while(getline(file,line)){

      TexturePack t;
      sf::Texture a;

      tmp = line.substr(0,line.find(" "));
      assert(a.loadFromFile(tmp));
      t.texture = a;

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
        t.nbFrames.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
        tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.nbFrames.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
        t.widthSprite.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
        tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.widthSprite.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(0,line.find(" "));
      t.heightSprite = atoi(tmp.c_str());

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
        t.offsetX.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
        tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.offsetX.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
        t.offsetY.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
        tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.offsetY.push_back(atoi(tmp.c_str()));

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
        t.isLoop.push_back(tmp.substr(0,tmp.find(",")).compare("T")==0);
        tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.isLoop.push_back(tmp.compare("T")==0);

      line = line.substr(line.find(" ")+1);
      tmp = line.substr(1,line.find(" "));
      while(tmp.find(",")!=std::string::npos){
        t.fps.push_back(atoi(tmp.substr(0,tmp.find(",")).c_str()));
        tmp = tmp.substr(tmp.find(",")+1);
      }
      tmp.pop_back();
      t.fps.push_back(atoi(tmp.c_str()));

      t.ID = texVector.size();
      texVector.push_back(t);

    }
    file.close();
  }
}


