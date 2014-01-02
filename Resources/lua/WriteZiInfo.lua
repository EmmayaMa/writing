-----------------------------------------
--��װ��д�������ݽṹ
--�� �ʶ� �ʻ� ���ο������������� POINT BD BH RECT
--TODO ������ģʽ���óɡ�V��
--TODO ��д����Ϣ��һ��: ����ܶȽ��е��� && �ֵĴ�С���з���
-----------------------------------------


local setmetatable = setmetatable
local pairs = pairs
local string = string
local tonumber = tonumber
local print = print
local math = math
local table =  table
local type = type

module("WriteZiInfo")
POINT = { GeoType = "KPOINT", x = 0, y = 0}
--ptSet { {x,y} {x,y} {x,y}���� }
BD = { GeoType = "KBD", ptSet = {} }
--BDSet {bd1 bd2 bd3}
--InflectionPoint ��ŵ��ǹյ������
BH = { GeoType = "KBH", ptSet = {}, InflectionPoint = {}, BDSet = {} }
--BHIdxSet {1,2,3}
RECT = { GeoType = "KRECT", BHIdxSet = {}, Edges = {left = -1, right = -1, top = -1,bottom = -1} }
--strokeStrings = {"x/y����","x/y����"}
--strokes = {bh1,bh2,bh3}
WriteHZ = { strokeNum = 0, strokes = {}, strokeStrings = {}  }

--##### �趨��׼������Ϣ begin#####--
local stdHZStruct = nil
function setStdHZ(stdHZ)
	stdHZStruct = stdHZ
end


--split ������sep�Ǵ��з��ַ�����signΪ�ָ��ַ�
function string:split(sep,sign)
	local sep, fields = sep or "\t", {}
	local pattern = string.format("([^"..sign.."]+)", sep)
	self:gsub(pattern, function(c) fields[#fields+1] = c end)
	return fields
end


--##### �趨��׼������Ϣ end#####--

--##### �� begin#####--
function POINT:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end
--##### �� end#####--

--##### �ʶ� begin#####--
function BD:new(o)
	local o = o or {}
	o.ptSet = {}
	setmetatable(o,self)
	self.__index = self
	return o
end
--##### �ʶ� end#####--

--##### �ʻ�begin#####--
function BH:new(o)
	local o = o or {}
	o.ptSet = {}
	o.InflectionPoint = {}
	o.BDSet = {}
	setmetatable(o,self)
	self.__index = self
	return o
end

--���㼯�ַ����ָ����ʼ���ʻ��ĵ㼯
function BH:splitPoints(ptStr)
	local ptSet = {}
	for strx,stry in string.gmatch(ptStr,"(%d+)/(%d+)") do
		local pt = {}
		pt.x = tonumber(strx)
		pt.y = tonumber(stry)
		ptSet[#ptSet+1] = pt
	end
	self.ptSet = ptSet
end

function sortingFun(a,b)
	if b.angle < a.angle then
			return false
	elseif b.angle > a.angle then
			return true
	else
			return false
	end
end

function BH:getStrokeBDNum(bh)

	local n_step = 5			--lua������1��ʼ
	local n_curIdx = n_step+1
	local n_preIdx = 1
	local n_postIdx = 2*n_step+1
	local angleArr = {}
	--������Ӧ�ĽǶ�
	for i = n_curIdx,(#self.ptSet)-n_step do
		local ele = {}
		local angle = self:calAngle(n_preIdx,i,n_postIdx)
		ele.pos = i
		ele.angle = angle
		table.insert(angleArr,ele)
		n_preIdx = n_preIdx+1
		n_postIdx= n_postIdx+1
	end
	--�ѽǶȰ��մ�С��������
	table.sort(angleArr,sortingFun)

	local nCandidateNum = #angleArr;
	if(nCandidateNum == 0) then
		return 1
	end
	local CInflectionPts = {}		--�洢��ѡ�յ������


	local f_angleThres = 12/18*3.14;
	for p = 1,nCandidateNum do
		local cFlag = false
		for q = 1,#CInflectionPts do
			if( math.abs(angleArr[p].pos - CInflectionPts[q]) < n_step) then
				cFlag = true
			end
		end
		if (cFlag == false) then
			if(angleArr[p].angle < f_angleThres) then
				CInflectionPts[#CInflectionPts+1] = angleArr[p].pos
			end
		end
	end

	if ( #CInflectionPts <= 1 ) then
		return #CInflectionPts+1
	end

	table.sort(CInflectionPts)

	return #CInflectionPts+1

end



--����ʻ��յ�
function BH:CalInflectionPoint(BDNum)
	local n_step = 5			--lua������1��ʼ
	if( #self.ptSet <2*n_step+1) then
		return
	end
	local n_curIdx = n_step+1
	local n_preIdx = 1
	local n_postIdx = 2*n_step+1
	local angleArr = {}
	--������Ӧ�ĽǶ�
	for i = n_curIdx,(#self.ptSet)-n_step do
		local ele = {}
		local angle = self:calAngle(n_preIdx,i,n_postIdx)
		ele.pos = i
		ele.angle = angle
		table.insert(angleArr,ele)
		n_preIdx = n_preIdx+1
		n_postIdx= n_postIdx+1
	end
	--�ѽǶȰ��մ�С��������
	table.sort(angleArr,sortingFun)
	local nCandidateNum = (BDNum-1)*10;
	if(nCandidateNum > #angleArr ) then
		nCandidateNum = #angleArr
	end
	local CInflectionPts = {}		--�洢��ѡ�յ������
	--ѡ�������BDNum+1���յ㣬�洢��CInflectionPts��
	local f_angleThres = 12/18*3.14;
	for p = 1,nCandidateNum do
		local cFlag = false
		for q = 1,#CInflectionPts do
			if( math.abs(angleArr[p].pos - CInflectionPts[q]) < n_step) then
				cFlag = true
			end
		end
		if (cFlag == false) then
			if(angleArr[p].angle < f_angleThres) then
				CInflectionPts[#CInflectionPts+1] = angleArr[p].pos
			end
			if(#CInflectionPts == BDNum+1) then
				break
			end
		end
	end

	--�����һ��CInflectionPts ѡ���Ĺյ�����С��(BDnum -1), then select again
	if( #CInflectionPts < BDNum-1) then
		for i = 1,#CInflectionPts do --	���
			CInflectionPts[i] = nil
		end
		for p = 1,nCandidateNum do
			local cFlag = false
			for q = 1,#CInflectionPts do
				if( math.abs(angleArr[p].pos - CInflectionPts[q]) < n_step) then
					cFlag = true
				end
			end
			if (cFlag == false) then
				CInflectionPts[#CInflectionPts+1] = angleArr[p].pos
				if(#CInflectionPts == BDNum-1) then
					break
				end
			end
		end
	end
	--��CInflectionPts�м���ѡ�����չյ㣬
	--������Ҫ��Ϊ�����αʻ���˵Ķ�������С�յ�������
	local n_prePos
	local n_postPos
	table.sort(CInflectionPts)

	if(#CInflectionPts <= 0) then
		return
	end

	if(#CInflectionPts == BDNum-1) then
		n_prePos = 1
		n_postPos = #self.ptSet
		self.InflectionPoint = CInflectionPts
	elseif(#CInflectionPts == BDNum) then
		local pos1 = CInflectionPts[1]
		local pos2 = CInflectionPts[#CInflectionPts]
		local diff1 = pos1 - 1
		local diff2 = #self.ptSet - pos2
		if(diff1 > diff2) then
			n_prePos = 1
			n_postPos = CInflectionPts[#CInflectionPts]
			table.remove(CInflectionPts,#CInflectionPts)
		else
			n_prePos = CInflectionPts[1]
			n_postPos = #self.ptSet
			table.remove(CInflectionPts,1)
		end
		self.InflectionPoint = CInflectionPts
	elseif(#CInflectionPts == BDNum+1) then
		n_prePos = CInflectionPts[1]
		n_postPos = CInflectionPts[#CInflectionPts]
		table.remove(CInflectionPts,1)
		table.remove(CInflectionPts,#CInflectionPts)
		self.InflectionPoint = CInflectionPts
	else
		n_prePos = 1
		n_postPos = #self.ptSet
		self.InflectionPoint = CInflectionPts
	end
	--����ʻ����˿��ܵĶ�����
	self:clearEndPoints(n_prePos,n_postPos)
end




--����curIdx��Ӧ�ĽǶ�
function BH:calAngle(preIdx, curIdx, postIdx)
	local prePt = self.ptSet[preIdx]
	local curPt = self.ptSet[curIdx]
	local postPt = self.ptSet[postIdx]
	local vecX = {}
	local vecY = {}
	vecX.x = prePt.x - curPt.x
	vecX.y = prePt.y - curPt.y
	vecY.x = postPt.x - curPt.x
	vecY.y = postPt.y - curPt.y
	disX = math.sqrt(vecX.x*vecX.x + vecX.y*vecX.y)
	disY = math.sqrt(vecY.x*vecY.x + vecY.y*vecY.y)
	cosXY = ( vecX.x*vecY.x + vecX.y*vecY.y )/(disX*disY)
	return math.acos(cosXY)
end

--����ʻ����˿����еĶ���
function BH:clearEndPoints(n_prePos, n_postPos)
	--�ȴ�ptset����������ƶ��յ������λ��
	if (n_prePos == 1 and n_postPos == #self.ptSet) then
		return
	end
	if n_postPos ~= #self.ptSet then
		local postPoint = self.ptSet[n_postPos]
		local lastPoint = self.ptSet[#self.ptSet]
		local postDis = math.sqrt(math.pow(lastPoint.x - postPoint.x,2) + math.pow(lastPoint.y - postPoint.y,2))
		if postDis < 15 then
		for i = #self.ptSet,n_postPos+1,-1 do
			table.remove(self.ptSet,i)
			end
		end
	end
	if n_prePos ~= 1 then
		local prePoint = self.ptSet[n_prePos]
		local firstPoint = self.ptSet[1]
		local preDis = math.sqrt(math.pow(prePoint.x - firstPoint.x,2) + math.pow(prePoint.y - firstPoint.y,2))
		if predis < 15 then
			for i = 1, n_prePos-1 do
			table.remove(self.ptSet,1)
			end
			--�ƶ��յ�����������������λ��
			for i = 1,#self.InflectionPoint do
				self.InflectionPoint[i] = self.InflectionPoint[i] - n_prePos+1
			end
		end
	end
end

--���ݹյ���Ϣ����ʶ�
function BH:initBDSet()
	local prepos = 1
	for i = 1, #self.InflectionPoint do
		local curpos = self.InflectionPoint[i]
		local bd = BD:new()
		for j = prepos, curpos do
			bd.ptSet[#bd.ptSet+1] = self.ptSet[j]
		end
		self.BDSet[#self.BDSet+1] = bd
		prepos = self.InflectionPoint[i]+1
	end
	local bd = BD:new()
	for i = prepos, #self.ptSet do
		bd.ptSet[#bd.ptSet+1] = self.ptSet[i]
	end
	self.BDSet[#self.BDSet+1] = bd
end
--##### �ʻ� end#####--

--#####���ο� begin#####--

--���ο��캯��
function RECT:new(o)
	local o = o or {}
	o.BHIdxSet = {}
	o.Edges = {left = -1, right = -1, top = -1,bottom = -1}
	setmetatable(o,self)
	self.__index = self
	return o
end
--#####���ο� end#####--




--#####��д�� begin#####--

function WriteHZ:new()
	local o = o or {}
	o.strokes = {}
	o.strokeStrings = {}
	setmetatable(o,self)
	self.__index = self
	return o
end




--------����д�ֱʻ�Ӧ���Ƚ��е��ܶȵĵ����ٽ��й�һ��
function getDistance(pt1,pt2)
	local dis = math.sqrt( math.pow(pt1.x - pt2.x,2) + math.pow(pt1.y - pt2.y,2))
	return dis
end

--����һ���ʻ��ĳ���
function getLength(ptSet)
	local length = 0.0
	for i = 1,#ptSet-1 do
		length = length + getDistance(ptSet[i],ptSet[i+1])
	end
	return length
end

function isIntable(ele,list)
	for j = 1,#list do
		if(ele.x == list[j].x and ele.y == list[j].y) then
			return true
		end
	end
	return false
end

--�з��ַ���
function splitPoints(ptStr,ptSet)
	for strx,stry in string.gmatch(ptStr,"(%d+)/(%d+)") do
		local pt = {}
		pt.x = tonumber(strx)
		pt.y = tonumber(stry)
		ptSet[#ptSet+1] = pt
	end
end

--���ڵ�Ĳ�ֵ ptSet �� dstPts ��ÿһ���ʻ��ĵ㼯
function adjustPtDensity(ptSet,dstPts)
	local nCount = getLength(ptSet)
	countInter,countFloat = math.modf (nCount)
	if (countFloat > 0.5) then
		nCount = countInter + 1
	else
		nCount = countInter
	end
	srcPts = {}
	for i = 1, #ptSet do
		srcPts[i] = ptSet[i]
	end
	local I  = 1
	local D = 0.0


	local xInter,xFloat = math.modf(srcPts[1].x)
	local yInter,yFloat = math.modf(srcPts[1].y)
	if ( xFloat > 0.5 ) then
		xInter = xInter + 1
	end
	if ( yFloat >0.5 ) then
		yInter = yInter + 1
	end
	dstPts[1] = {}
	dstPts[1].x = xInter
	dstPts[1].y = yInter

	local i = 2
	while (true) do
		local pt1 = srcPts[i-1]
		local pt2 = srcPts[i]
		local d = getDistance(pt1,pt2)
		if ( (D + d) >= I ) then
			local qx = pt1.x + ( (I - D)/d )*(pt2.x - pt1.x)
			local qy = pt1.y + ( (I - D)/d )*(pt2.y - pt1.y)
			local tmpPT = {}
			xInter,xFloat = math.modf (qx)
			yInter,yFloat = math.modf (qy)

			if (xFloat > 0.5) then
				xInter = xInter + 1
			end

			if (yFloat > 0.5) then
				yInter = yInter + 1
			end
			tmpPT.x = xInter
			tmpPT.y = yInter
			dstPts[#dstPts+1] = tmpPT
			if (isIntable(tmpPT,srcPts) == false) then
				table.insert(srcPts,i,tmpPT)
			end
			D = 0.0
		else
			D = D + d
		end
		i = i + 1
		if( i == #srcPts + 1) then
			break
		end
	end
end

	m_norWidth = 128
	m_norHeight = 128
	m_nLeftMargine = 0
	m_nUpMargine = 0

--���������ֵķ�������
function calZoomRatio (strokeStrsArr,zoomRatio,xOffset,yOffset)
	local n_minLeft = 0
	local n_maxRight = 0
	local n_minUp = 0
	local n_maxDown = 0
	local onestroke = {}
	for j = 1,#strokeStrsArr do
		onestroke = strokeStrsArr[j]
		local ptSet = {}
		splitPoints(onestroke,ptSet)

		for i =1,#ptSet do
			if (n_minLeft > ptSet[i].x) then
				n_minLeft = ptSet[i].x
			end

			if(n_maxRight < ptSet[i].x) then
				n_maxRight = ptSet[i].x
			end

			if(n_minUp > ptSet[i].y) then
				n_minUp = ptSet[i].y
			end

			if(n_maxDown < ptSet[i].y) then
				n_maxDown = ptSet[i].y
			end
		end
	end
	local n_preWidth = n_maxRight - n_minLeft
	local n_preHeight = n_maxDown - n_minUp
	if (n_preWidth == 0 and n_preHeight == 0) then
		zoomRatio = 1.0
		xOffset = m_norWidth/2  -n_minLeft
		yOffset = m_norHeight/2 - n_minUp
	elseif (n_preWidth > n_preHeight) then
		xOffset = -n_minLeft
		yOffset = (n_preWidth - n_preHeight) / 2 - n_minUp
		zoomRatio = m_norWidth / n_preWidth
	else
		xOffset = ( n_preHeight - n_preWidth )/2 - n_minLeft
		yOffset = -n_minUp
		zoomRatio =  m_norHeight /n_preHeight
	end
end


--��һ�����ֵ
function WriteHZ:Normailize(strokeStrs)
	local zoomRatio = 1
	local xOffset = 0
	local yOffset = 0
	local strokeStrsArr = {}

	--midPtSet �Ǿ����������м�㼯 ÿһ�ʵ����е㼯���һ��Сtable
	local midPtSet = {}

	for i = 1,#strokeStrs do
		strokeStrsArr[#strokeStrsArr+1] = strokeStrs[i]
	end

	--1.�Ƚ��������ִ�С�ķ���
	calZoomRatio(strokeStrsArr,zoomRatio,xOffset,yOffset)
	for i = 1 ,#strokeStrsArr do
		local onestrokePtSet = {}
		local ptset = {}
		splitPoints(strokeStrsArr[i],ptset)
		for j =1 ,#ptset do
			local tmpPT = {}
			tmpPT.x = ( ptset[j].x + xOffset )*zoomRatio + m_nLeftMargine + 0.5
			tmpPT.y = ( ptset[j].y + yOffset )*zoomRatio + m_nUpMargine + 0.5
			onestrokePtSet[#onestrokePtSet+1] = tmpPT
		end
		midPtSet[#midPtSet+1] = onestrokePtSet
	end
	--������ɺ������������midPtSet��
	--2.��Ĳ�ֵ
	local tmp = {}
	for i = 1, #midPtSet do
		local prePtSet = midPtSet[i]
		local onePtSet = {}
		adjustPtDensity(prePtSet,onePtSet)
		tmp[#tmp+1] = onePtSet
	end
	return tmp
end



--------����д�ֱʻ�Ӧ���Ƚ��е��ܶȵĵ����ٽ��й�һ��

function WriteHZ:initialize(str)
	local strokeStrs = {}
	strokeStrs = str:split(str,"@")
	local dstStrokes = {}
	dstStrokes = self:Normailize(strokeStrs)
	self:initStrokeStrs(dstStrokes )
	self:initStrokeNum(#dstStrokes )
end

--��ʼ����д�ֱʻ�������Ϣ
function WriteHZ:initStrokeNum(strokeNum)
	self.strokeNum = strokeNum
end


--��ʼ����д�ֵ㼯��Ϣ
function WriteHZ:initStrokeStrs( strokeStrs )
	local Strs = {}
	for i = 1,#strokeStrs do
		local onestroke = ""
		for j = 1,#strokeStrs[i] do
			onestroke = onestroke .. strokeStrs[i][j].x .. "/"..strokeStrs[i][j].y .. "/"
		end
		Strs[#Strs+1] = onestroke
	end

	for i = 1,#Strs do
		self.strokeStrings[#self.strokeStrings+1] = Strs[i]
	end
	self:initStrokes()
end


--��ʼ���ʻ���Ϣ
function WriteHZ:initStrokes()
	for i=1,#self.strokeStrings do
		local str = self.strokeStrings[i]
		local onestroke = BH:new()
		onestroke:splitPoints(str)

		--��д�ֱʶ���Ŀ�Ķ�ȡ��Ӧ�ôӱ�׼����Ϣ��ȡ
		--local curStrokeBDNum = stdHZStruct:getStrokeBDNumByIdx(i)
		local curStrokeBDNum = onestroke:getStrokeBDNum(onestroke)
		--����յ�ͳ�ʼ���ʶ�
		onestroke:CalInflectionPoint(curStrokeBDNum)
		onestroke:initBDSet()
		self.strokes[#self.strokes+1] = onestroke
	end
end



--[[
--��ʼ���ʻ���Ϣ
function WriteHZ:initStrokes()
	--tmpPTSet {(x,y),(x,y)...}
	local tmpPTSet = {}
	for i=1,#self.strokeStrings do
		local str = self.strokeStrings[i]
		local onestroke = BH:new()
		onestroke:splitPoints(str)
		for j=1,#onestroke.ptSet do
			tmpPTSet[#tmpPTSet+1] = onestroke.ptSet[j]
		end
	end
	normalize(tmpPTSet)
end

--��Ϣ���

]]--
function WriteHZ:clearData()
	self.strokeNum = 0
	self.strokeStrings = {}
	self.strokes = {}
end

--#####��д�� end#####--
