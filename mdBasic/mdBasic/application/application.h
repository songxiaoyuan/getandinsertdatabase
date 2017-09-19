#pragma once
#include "../md/mdspi.h"
#include "../trader/traderspi.h"
#include "../basicFun/basicFun.h"
#include <iostream>

class application {
 public:
  application();
  //Ӧ�õ�������Ϣ�����ò���ǰ�õ�ַ���û����Ȼ�����Ϣ��
  void ConfigFun();
  // Ӧ�ó�ʼ������
  void Init();
  // Ӧ�����к���
  void Run();
  // �����û����е�¼
  void MdUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId,
                   TThostFtdcPasswordType passwd);
  //trader �û����е�½
  void TraderUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId,
                   TThostFtdcPasswordType passwd);
  // ���Ĺ��ĵĺ�Լ����
  void SubscribeMarketData();
  //�õ����еĺ�Լid
  void GetAllInstrumentIds();

  virtual ~application();

 protected:
 private:
  int requestid_;
   //�û���¼��Ҫ��ǰ�õ�ַ
	char* MDFRONT;
	char* TRADEFRONT;

//�û���¼��Ҫ����Ϣ��
	TThostFtdcBrokerIDType APPID;
	TThostFtdcUserIDType USERID;
	TThostFtdcPasswordType PASSWD;

//���ĵ������б�
	char** PPINSTRUMENTID;
	int NUMOFINSTRUMENTID;
  // �����������ʱ��md��spi��
   CtpMdSpi* pMdSpi;
   CtpTraderSpi* pTraderSpi;

  //�����������ʱ��md api
  CThostFtdcMdApi* pMdApi;
  CThostFtdcTraderApi* pTraderApi;
  
};

