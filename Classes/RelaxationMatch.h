// RelaxationMatch.h: interface for the RelaxationMatch class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __RelaxationMatch_H__
#define __RelaxationMatch_H__

// #if _MSC_VER > 1000
// #pragma once
// #endif // _MSC_VER > 1000

#include "TemplateCharacter.hpp"
#include "ScriptCharacter.hpp"

//////////////////////////////////////////////////////////
struct candidate  //���ڵ�������ʱ����ʱ�������Լ��ɳ�ƥ��Ľ����ȡ
{
	int h;   //��д�ʶ�����
	int k;   //ģ��ʶ�����
	float probability;
};

struct multicandidate  //���ڵ�������ʱ����ʱ�������Լ��ɳ�ƥ��Ľ����ȡ
{
	list<int> hlist;   //��д�ʶ�����
	list<int> klist;   //ģ��ʶ�����
	float probability;
};

class ComponentMatch  //����ƥ�����
{
public:
	list<candidate> havemath;  //��ƥ��ʶ�
	list<int> nomatch_model_seg; //δƥ���ģ���ֱʶ�

	////////////////////////////////////
	//���ڰ�Χ�еĹ���
	list<int>  top_key_segments;
	list<int>  bottom_key_segments;
	list<int>  left_key_segments;
	list<int>  right_key_segments;
	////////////////////////////////////

	ComponentMatch();
	virtual ~ComponentMatch();
	
	///////
	ComponentMatch& operator=(const ComponentMatch& Right);    //��ֵ
	ComponentMatch(const ComponentMatch& Right); //��������
};

struct scriptpro
{
	int sh;
	float probability;
};

struct candidateforgreedy
{
	int mk; //ģ���ֱʶ�
	list<scriptpro> shlist; //��д�ֱʶδ����б�
};

struct conflictforgreedy
{
	candidate can1;  
	candidate can2;
};

struct boundingbox
{
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
};

////////////////////////////////////////////////////////
class RelaxationMatch  
{
public:
	RelaxationMatch();
	virtual ~RelaxationMatch();
	
	////////////////////////////////
	ScriptCharacter script;  //��д��
	TemplateCharacter model; //ģ����

	int iteration_times;     //��������
	float ** probability;    //ƥ����ʡ�probability[i][j]��ʾ��д�ֵ�i���ʶ���ģ���ֵ�j���ʶε�ƥ�����.
	                         //          ������ƥ��������ڣ�j���ڵ���0��С�ڵ���model_count��
	
	int **  updowncount;     //���ڼ�¼�ڵ���������ƥ����ʵ��������������ڼ��ٵ�����

	float**** compatibility;  //���ݳ̶ȡ�����compatibility[i][j][h][k]�����У�i��h��ʾ��д�ֱʶΣ�
	                          //          j��k��ʾģ���ֱʶΡ�����ʾ(i��j)(h��k)ͬʱƥ������ݳ̶ȡ�
	                          //          ȡֵ��Χ��[-1,1]�������˷�Χ����ʾ��д�ֱʶ��Ƕ��ʣ����ܲ������ݳ̶ȵļ��㡣

 	int script_count;        //��д�ʶ���
	int model_count;         //ģ��ʶ���  
	
	list<candidate> matchresult;  //һ��һƥ����
	list<multicandidate> multimatchresult; //һ�Զࡢ���һƥ����
	////////////////////////////////

	bool Inputcharacters(ScriptCharacter handwritten, TemplateCharacter modelwritten);
	void Initmatchprobability();
	void Initmatchcompatibility();

	void IterateOnce();   //����һ�Σ��鿴���
	void RelaxationExtraction();  //����15�����Һ󣬵������������ȡ�ɳ��㷨��ƥ������
	void processing_tiny_segments();//������д�ʻ������Խϴ���д������ıʶ��з��㷨���ܱ�֤������ȷ��
                                    //���ԣ����ɳ�ƥ��󣬵��ô˺�������һЩϸ���δƥ��ʶΡ�
                                    
	////////////////////////////////////////////////
	//���ɳ�ƥ���㷨����֮�󣬶���һЩ���͵�δƥ�����������Ӧ�Ĵ������
	void UnmatchExtension();              //�˹����������������д�ֺ�ģ������ͬʱ����δƥ��ʶ�(���ʳ���)��

	void ComplexStrokeAdjust();           //�˹���������������Ա��νϴ󡢱ʶν϶�ĸ��ӱʻ����е�����ȷ�ϡ�
	
	void NoiseExtension_forsingle();      //�˹��������������ģ�����е�ĳ���ʶ�����д���еĶ������Ӧ��
	void FreeExtension();                 //�˹�����������������������������д�ֺ�ģ�������Ծ�ͬʱ����δƥ��ʶΡ�

	void Noturning_Connection_Extension();//�˹����������������д���д���û�йյ�����������
	void Noturning_Broken_Extension();    //�˹����������������д���д��ڶϱ�������Ͽ���������ģ������û�йյ�
	void NoiseExtension_formulti();

protected:
	void Clearcontext();
	void Allocatecontext();


private:
	//������UnmatchExtension()ʹ��	
	void SortandReduce(list<ComponentMatch> &complist);  //���ɳ�ƥ���㷨���ƥ�������������������	
	CCPoint Evalute_position_forgreedy(int mk, ComponentMatch m_ComponentMatch, boundingbox modelbox,boundingbox sriptbox);//������ƥ��ʶΡ��Լ��Ѿ����ƺõİ�Χ�У�Ϊĳ��ģ��ʶι��ƺ�ѡ��д�ʶε�����λ��
	float Evalute_length_forgreedy(int mk, boundingbox modelbox,boundingbox sriptbox);//������ƥ��ʶΡ��Լ��Ѿ����ƺõİ�Χ�У�Ϊĳ��ģ��ʶι��ƺ�ѡ��д�ʶεĳ���
	list<candidateforgreedy> probabilityforgreedy(ComponentMatch m_ComponentMatch, list<int> nomatchscript, int passnumber);
	list<scriptpro> Evalute_prob_forgreedy(int model_seg, CCPoint center_pos, float mlen, ComponentMatch m_ComponentMatch,list<int> nomatchscript);
	void Evalute_boundingbox(ComponentMatch m_ComponentMatch,boundingbox &modelbox,boundingbox &scriptbox);
	
	list<conflictforgreedy> conflicttestforgreedy(list<candidateforgreedy> candidatelist);
	list<candidate> GreedyExtraction(list<candidateforgreedy> candidatelist, list<conflictforgreedy> conflictlist);
	bool checkcompatibility_for_Greedy(candidate& m_item, list<candidate>& m_res, list<conflictforgreedy>& conflictlist);


	//������ComplexStrokeAdjust()ʹ��
	list<candidate> merge_script_seg_for_multimatch(list<multicandidate> tempmultires);

	void process_stroke_heng_pei_wan_gou();
	void heng_pei_wan_gou_match_1(int start_sh, int start_mk, int sh_count, list<candidate>  &res, list<multicandidate> &tempmultires);
	void heng_pei_wan_gou_match_2(int m_seg1,int s_seg1, int m_seg2,int s_seg2,int m_seg3,int s_seg3,int m_seg4,int s_seg4, list<multicandidate>  &tempmultires);
		
	void process_stroke_wo_gou();
	void wo_gou_match(int mk_wo,int sh_wo, int mk_gou, int sh_gou, list<multicandidate> &tempmultires);

	void process_stroke_wan_gou();
	void wan_gou_match(int mk_wan,int sh_wan, int mk_gou,int sh_gou, list<multicandidate> &tempmultires);

	void process_stroke_xie_gou();
	void xie_gou_match(int mk_xie, int sh_xie, int mk_gou, int sh_gou, list<multicandidate> &tempmultires);

	void process_stroke_heng_zhe_wan_pie();
	void heng_zhe_wan_pie_match_1(int start_sh, int start_mk, int sh_count, list<candidate> &res, list<multicandidate>  &tempmultires);

	//������FreeExtension()����
	list<conflictforgreedy> conflicttestforfree(list<candidateforgreedy> candidatelist);
	list<scriptpro> Evalute_prob_forfree(int model_seg, CCPoint center_pos, float mlen, ComponentMatch m_ComponentMatch, list<int> nomatchscript);


	//ƥ�����Ĳ�ѯ	
	int Find_Match_for_Model_segment_in_single_result(int k);   //ֻ��matchresult����
	int Find_Match_for_script_segment_in_single_result(int sh); //ֻ��matchresult����       

	list<int> Find_Nomatch_normal_Scriptseg_in_both_reslult();  //ͬʱ��matchresult��multimatchresult����
	list<int> find_nomatch_modelseg_in_both_result();           //ͬʱ��matchresult��multimatchresult����

	list<int> find_match_for_modelseg_in_multiresult(int k); //ֻ��multimatchresult����
	//int find_multimatch_for_script_segment(int sh, list<int> &shlist);


};

#endif // __RelaxationMatch_H__