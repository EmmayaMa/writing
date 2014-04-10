local math = math
strokeRuleNode = {index = 0, codes = ""}
unitRuleNode = {index = 0, zistrokeRules = {}}

Pass2CStr = ""
--########################			��������				#############################
function string:split(sep,sign)
	local sep, fields = sep or "\t", {}
	local pattern = string.format("([^"..sign.."]+)", sep)
	self:gsub(pattern, function(c) fields[#fields+1] = c end)
	return fields
end

function superSplit(szFullString, szSeparator)
	local nFindStartIndex = 1
	local nSplitIndex = 1
	local nSplitArray = {}
	while true do
		local nFindLastIndex = string.find(szFullString, szSeparator, nFindStartIndex)
		if not nFindLastIndex then
		 nSplitArray[nSplitIndex] = string.sub(szFullString, nFindStartIndex, string.len(szFullString))
		 break
		end
		nSplitArray[nSplitIndex] = string.sub(szFullString, nFindStartIndex, nFindLastIndex - 1)
		nFindStartIndex = nFindLastIndex + string.len(szSeparator)
		nSplitIndex = nSplitIndex + 1
	end
	return nSplitArray
end

function trim(s)
	return (string.gsub(s,"^%s*(.-)%s*$","%1"))
end

--���ļ�����
function ReadFile(filename)
file = io.open(filename,"r")
local totalStr = ""
for line in file:lines() do
	totalStr = totalStr .. "\n"..line
end
file:close()
return totalStr
end
--#########################			��������			#######################################


--#########################	������д����Ϣ		 ########################################
local WriteZiStr = GetWriteInfoFromC()	--�ⲿ�ӿ�
local WZ = require("WriteZiInfo")
local writeHZ = WZ.WriteHZ:new()
writeHZ:initialize(WriteZiStr)
--#########################	������д����Ϣ		 ########################################


--ֻ��Ҫ�ּ���Ĵ��뼴��
--#########################	װ�ش���		 ########################################
--local ZiName = GetZiNameFromC()				--�ⲿ�ӿ�
--local filepath = "ZiList\\"..ZiName.."\\rules.txt"
--local RuleStr = ReadFile(filepath)
--local strZiRule = RuleStr
local strZiRule = GetRulesFromC();

--װ���ּ������ 	ZiRuleList = {{index = 1 , codes = "..."},{index = 2 , codes = "..."},{index = 3 , codes = "..."},...}
strZiRule  = string.gsub(strZiRule , "//##begin", "" )
strZiRule  = string.gsub(strZiRule , "//##end", "" )
strZiRule  = string.gsub(strZiRule , "//##", "//##--" )
strZiRule  = trim(strZiRule)


local ZiRuleList = {}
local tmpZiRuleList = {}
tmpZiRuleList = superSplit(strZiRule ,"//##")
table.remove(tmpZiRuleList,1)
for i = 1,#tmpZiRuleList do
	local oneNode = {}
	oneNode.index = i-1
	oneNode.codes = tmpZiRuleList[i]
	ZiRuleList[#ZiRuleList+1] = oneNode
end


--�������ʻ����ӱʻ���Ŀ�ж����
local NewZiRuleArr = {}
local str1 = "if(bhNum == "
local str2 = ") then ".."\n"
local str3 = "end".."\n"
for i = 1,#ZiRuleList do
	local newRule = str1.. tostring (i) ..str2
	local newBH = ""
	if ( i > 1 ) then
		newBH = "bh"..tostring (i - 2) .. " = GetBH(" ..tostring(i - 2) .. ");"
	end
	newRule  = newRule  .. newBH .. ZiRuleList[i].codes.."\n"..str3
	NewZiRuleArr[#NewZiRuleArr+1] = newRule
end



baseFuncs = require("BaseLib")
baseFuncs.setWriteZiInfo(writeHZ)
baseFuncs.setWZEnv(WZ)

--�˴���Ҫ���ⲿC�������ӽӿ�
--local strokeLevel =  GetStrokeLevelFromC()

function RunZiRule(bhNum)
	local header = [[setmetatable(baseFuncs,{__index= _G})
	setfenv(1,baseFuncs)]] .."\n"
	local pre = header .."\n" .."local bhNum ="..tostring (bhNum) .."\n".."local bl = 3"
	local allzirule = table.concat(NewZiRuleArr)
	local result = pre.."\n"..allzirule



	f = loadstring(result)
	f()
end

local bhNum = writeHZ.strokeNum
RunZiRule(bhNum)
Pass2CStr = baseFuncs.allInfoStr
return Pass2CStr


