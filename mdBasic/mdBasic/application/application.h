#pragma once
#include "../md/mdspi.h"
#include "../trader/traderspi.h"
#include "../basicFun/basicFun.h"
#include <iostream>

class application {
 public:
  application();
  //应用的配置信息，配置产生前置地址，用户名等基本信息。
  void ConfigFun();
  // 应用初始化函数
  void Init();
  // 应用运行函数
  void Run();
  // 订阅用户进行登录
  void MdUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId,
                   TThostFtdcPasswordType passwd);
  //trader 用户进行登陆
  void TraderUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId,
                   TThostFtdcPasswordType passwd);
  // 订阅关心的合约编码
  void SubscribeMarketData();
  //得到所有的合约id
  void GetAllInstrumentIds();

  virtual ~application();

 protected:
 private:
  int requestid_;
   //用户登录需要的前置地址
	char* MDFRONT;
	char* TRADEFRONT;

//用户登录需要的信息。
	TThostFtdcBrokerIDType APPID;
	TThostFtdcUserIDType USERID;
	TThostFtdcPasswordType PASSWD;

//订阅的行情列表
	char** PPINSTRUMENTID;
	int NUMOFINSTRUMENTID;
  // 保存程序运行时的md的spi。
   CtpMdSpi* pMdSpi;
   CtpTraderSpi* pTraderSpi;

  //保存程序运行时的md api
  CThostFtdcMdApi* pMdApi;
  CThostFtdcTraderApi* pTraderApi;
  
};

