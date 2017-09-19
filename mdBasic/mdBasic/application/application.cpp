#include "application.h"


application::application() {
  // ctor
	requestid_ = 1;
}

void application::ConfigFun() {
    //�˺�����Ҫ��������ȡһЩ������Ϣ����ǰ�õ�ַ�ȡ�ͨ����ȡconfig.txt�������Ϣ��
	string path = "config.txt";
	unordered_map<string,string> ret =  GetConfigInfo(path);
	MDFRONT=ChangeStrToChar(ret["MDFRONT"]);
	TRADEFRONT=ChangeStrToChar(ret["TRADERFRONT"]);
	strcpy(APPID,ChangeStrToChar(ret["APPID"]));
	strcpy(USERID,ChangeStrToChar(ret["USERID"]));
	strcpy(PASSWD,ChangeStrToChar(ret["PASSWD"]));
	
}

void application::Init() {

  //��ʼ��MDApi
  pMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
  pMdSpi = new CtpMdSpi();  //�����ص����������MdSpi
  pMdApi->RegisterSpi(pMdSpi);        // �ص�����ע��ӿ���
  pMdApi->RegisterFront(MDFRONT);     // ע������ǰ�õ�ַ
  pMdApi->Init();                     //�ӿ��߳�����, ��ʼ����

  	//��ʼ��traderApi
    pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	pTraderSpi = new CtpTraderSpi(pTraderApi);
	pTraderApi->RegisterSpi((CThostFtdcTraderSpi*)pTraderSpi);			// ע���¼���
	pTraderApi->SubscribePublicTopic(THOST_TERT_RESTART);					// ע�ṫ����
	pTraderApi->SubscribePrivateTopic(THOST_TERT_RESTART);			  // ע��˽����
	pTraderApi->RegisterFront(TRADEFRONT);	// ע�ύ��ǰ�õ�ַ
	pTraderApi->Init();
}

void application::Run() {
  int i;
  cerr << "-----------------------------------------------" << endl;
  cerr << "[1] userLogin     "<<endl;
  cerr << "[2] userSubscribe "<< endl;
  cerr << "[3] Exit    " <<endl;
  cerr << "----------------------------------------------" << endl;
  while (1) {
    cin >> i;
    switch (i) {
      case 1: {
        //�û���¼��Ϣ������md��¼��trader��¼
        // MD�û���ʼ��¼
        MdUserLogin(APPID, USERID, PASSWD);
		//trader �û���ʼ��½
		TraderUserLogin(APPID, USERID, PASSWD);
        break;
      }
      case 2: {
        // ��ѯ���еĺ�Լid��Ϣ��
        GetAllInstrumentIds();
        break;
      }
	  case 3: {
        // �������еĺ�Լ��Ϣ
        SubscribeMarketData();
        break;
      }
      case 4: {
        // �����˳������߿�������Ĳ�����
        exit(0);
        break;
      }
    }
  }
  pMdApi->Join();
}

void application::MdUserLogin(TThostFtdcBrokerIDType appId,
                              TThostFtdcUserIDType userId,
                              TThostFtdcPasswordType passwd) {
  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, APPID);
  strcpy(req.UserID, userId);
  strcpy(req.Password, passwd);
  int ret = pMdApi->ReqUserLogin(&req, ++requestid_);
  cerr << " req | send login..." << ((ret == 0) ? "success" : "fail") << endl;
}


void application::TraderUserLogin(TThostFtdcBrokerIDType appId,
                              TThostFtdcUserIDType userId,
                              TThostFtdcPasswordType passwd) {
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, APPID);
   strcpy(req.UserID, userId);
   strcpy(req.Password, passwd);
   int ret = pTraderApi->ReqUserLogin(&req, ++requestid_);
    cerr<<" request | send login in..."<<((ret == 0) ? "succeed" :"failed") << endl;

	//��ʼ���㵥������ȷ��

	pTraderSpi->ReqQrySettlementInfo(appId,userId,requestid_);
	pTraderSpi->ReqSettlementInfoConfirm(appId,userId,requestid_);
}

void application::GetAllInstrumentIds(){
	CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));   
	int ret = pTraderApi->ReqQryInstrument(&req, ++requestid_);
    cerr<<" request |send get all instruments..."<<((ret == 0) ? "succeed" :"failed") << endl;
}

void application::SubscribeMarketData() {
	set<string> instrumentIds = pTraderSpi->getSetInstruments();
	set<string>::iterator iter=instrumentIds.begin();  
      
    while(iter!=instrumentIds.end())  
    {  
        cout<<*iter<<endl;  
		char** tmp = new char* [1];
		tmp[0] = ChangeStrToChar(*iter);
		int ret = pMdApi->SubscribeMarketData(tmp, 1);
        cerr << " req | send market md... " << ((ret == 0) ? "success" : "fail") << endl;

        ++iter;  
    }  
}


application::~application()
{
    //dtor
}

