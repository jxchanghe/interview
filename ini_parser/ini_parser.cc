#include "ini_parser.h"


namespace qh
{
	void Trim(std::string& str, const std::string & ChrsToTrim = " \t\n\r", int TrimDir = 0)
	{
		size_t startIndex = str.find_first_not_of(ChrsToTrim);
		if (startIndex == std::string::npos){str.erase(); return;}
		if (TrimDir < 2) str = str.substr(startIndex, str.size()-startIndex);
		if (TrimDir != 1) str = str.substr(0, str.find_last_not_of(ChrsToTrim) + 1);
	}

	INIParser::INIParser()
	{
		
	}

	INIParser::~INIParser()
	{
		
	}

	bool INIParser::Parse(const std::string& ini_file_path)
	{
		std::string sFileData("");
		std::ifstream inFile (ini_file_path.c_str());
		
		if (!inFile.is_open())
		{
			return false;
		}
		
		std::string str;
		while(std::getline(inFile, str))
		{
			Trim(str);
			sFileData = sFileData + str  + "\n";
		}
		
		Parse(sFileData.c_str(), sFileData.size());
		inFile.close();
		return true;
	}

	bool INIParser::ParseOneLine(std::string& strLine, std::string& curSection, const std::string& key_value_seperator)
	{
		if (strLine.find('[') != std::string::npos)								
		{		
			strLine.erase(strLine.begin());											
			strLine.erase(strLine.find(']'));																																
			curSection = strLine;
		}
		
		if(strLine.find(key_value_seperator) != std::string::npos)								
		{					
			std::string key = strLine.substr(0, strLine.find(key_value_seperator));							
			std::string value = strLine.substr(strLine.find(key_value_seperator) + key_value_seperator.size());	
			mapIniData.insert(std::pair<std::string, std::string>(curSection + key, value));
		}

		return true;
	}

	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator , const std::string& key_value_seperator )
	{
		size_t lineSeperatorLen = line_seperator.size();
		std::string strIniData(ini_data, ini_data_len);
		size_t pos;
		std::string curSection("");

		//末尾追加一个行分隔符，方便处理
		strIniData += line_seperator;
		pos = strIniData.find(line_seperator);
		while (pos != std::string::npos)
		{
			std::string strLine = strIniData.substr(0, pos);
			strIniData.erase(0, pos + lineSeperatorLen);
			pos = strIniData.find(line_seperator);
			
			Trim(strLine);
			if (strLine.size() > 0)
			   ParseOneLine(strLine, curSection, key_value_seperator);
		}
	
		return true;
	 }

	 const std::string& INIParser::Get(const std::string& key, bool* found)
	 {
		 std::map<std::string , std::string >::iterator l_it;; 
		 l_it=mapIniData.find(key);
		
		 if(l_it == mapIniData.end())
		 {
			const static std::string nullResult("");

		   if (NULL != found)   
			    *found = false;
            return nullResult;
		 }
		 else
		 {
			if (NULL != found)  
				*found = true;
		    return mapIniData[key];
		 }
	 }

	 const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
	 {
		return Get(section + key, found);
	 }
}