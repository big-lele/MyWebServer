#include "webserver/config.h"
#include "webserver/log.h"
#include <yaml-cpp/yaml.h>

//约定优于配置
webserver::ConfigVar<int>::ptr g_int_value_config =
        webserver::Config::Lookup("system.port", (int)8080, "system port");

webserver::ConfigVar<float>::ptr g_float_value_config =
        webserver::Config::Lookup("system.value", (float)10.2f, "system value");

webserver::ConfigVar<std::vector<int> >::ptr g_int_vec_value_config =
        webserver::Config::Lookup("system.int_vec", std::vector<int>{1, 2}, "system int vec");

webserver::ConfigVar<std::list<int> >::ptr g_int_list_value_config =
        webserver::Config::Lookup("system.int_list", std::list<int>{1, 2}, "system int list");

webserver::ConfigVar<std::set<int> >::ptr g_int_set_value_config =
        webserver::Config::Lookup("system.int_set", std::set<int>{1, 2}, "system int set");

webserver::ConfigVar<std::unordered_set<int> >::ptr g_int_uset_value_config =
        webserver::Config::Lookup("system.int_uset", std::unordered_set<int>{1, 2}, "system int uset");

webserver::ConfigVar<std::map<std::string, int> >::ptr g_str_int_map_value_config =
        webserver::Config::Lookup("system.str_int_map", std::map<std::string, int>{{"k", 2}}, "system str int map");

webserver::ConfigVar<std::unordered_map<std::string, int> >::ptr g_str_int_umap_value_config =
        webserver::Config::Lookup("system.str_int_umap", std::unordered_map<std::string, int>{{"k", 2}}, "system str int umap");

void print_yaml(const YAML::Node& node, int level){
        if(node.IsScalar()){
	        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
			<< node.Scalar() << " - " << node.Type() << " - " << level;
	}
	else if(node.IsNull()){
	        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                        << "NULL - " << node.Type() << " - " << level;
	}
	else if(node.IsMap()){
	        for(auto it = node.begin();
		        it != node.end(); ++it){
			WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                                << it->first << " - " << it->second.Type() << " - " << level;
		        print_yaml(it->second, level + 1);
		}
	}
	else if(node.IsSequence()){
	        for(size_t i = 0; i < node.size(); ++i){
		        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << std::string(level * 4, ' ')
                                << i << " - " << node[i].Type() << " - " << level;
                        print_yaml(node[i], level + 1);
		}
	}
}

void test_yaml(){
        YAML::Node root = YAML::LoadFile("/root/webServer/MyWebServer/bin/conf/log.yml");
        print_yaml(root, 0);

	WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << root.Scalar();
}

void test_config(){
        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << "before: " << g_float_value_config->toString();

#define XX(g_var, name, prefix) \
	{ \
	        auto& v = g_var->getValue(); \
                for(auto& i : v){ \
                        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << #prefix " " #name ": " << i; \
                } \
		WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
	}

#define XX_M(g_var, name, prefix) \
        { \
                auto& v = g_var->getValue(); \
                for(auto& i : v){ \
                        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << #prefix " " #name ": {"  \
			        << i.first << " - " << i.second << "}"; \
                } \
                WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
        }

	XX(g_int_vec_value_config, int_vec, before);
	XX(g_int_list_value_config, int_list, before);
	XX(g_int_set_value_config, int_set, before);
	XX(g_int_uset_value_config, int_uset, before);
	XX_M(g_str_int_map_value_config, str_int_map, before);
	XX_M(g_str_int_umap_value_config, str_int_umap, before);

	YAML::Node root = YAML::LoadFile("/root/webServer/MyWebServer/bin/conf/log.yml");
	webserver::Config::LoadFromYaml(root);

	WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << "after: " << g_float_value_config->toString();

	XX(g_int_vec_value_config, int_vec, after);
        XX(g_int_list_value_config, int_list, after);
	XX(g_int_set_value_config, int_set, after);
	XX(g_int_uset_value_config, int_uset, after);
	XX_M(g_str_int_map_value_config, str_int_map, after);
	XX_M(g_str_int_umap_value_config, str_int_umap, after);
}

int main(int argc, char** argv){
	//test_yaml();
	test_config();
        return 0;
}
