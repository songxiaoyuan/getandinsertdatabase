#ifndef ORDER_TRADERSPI_H_
#define ORDER_TRADERSPI_H_
#pragma once

#include "../api/ThostFtdcTraderApi.h"
#include "../basicFun/basicFun.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;


class CtpTraderSpi : public CThostFtdcTraderSpi
{
public:
   CtpTraderSpi(CThostFtdcTraderApi* api):pUserApi(api){};

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);



	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);


public:
	///�û���¼����
	void ReqUserLogin(TThostFtdcBrokerIDType	appId,
	        TThostFtdcUserIDType	userId,	TThostFtdcPasswordType	passwd,int &requestId);
    ///�����ѯͶ���߽�����
	void ReqQrySettlementInfo(TThostFtdcBrokerIDType	vAPPID,
	        TThostFtdcUserIDType	vUserId,int &requestId);
	///Ͷ���߽�����ȷ��
	void ReqSettlementInfoConfirm(TThostFtdcBrokerIDType	vAPPID,
	        TThostFtdcUserIDType	vUserId,int &requestId);
	///�����ѯ��Լ
	void ReqQryInstrument(TThostFtdcInstrumentIDType instId,int &requestId);

	/// �Ƿ��յ��ɹ�����Ӧ
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);

	set<string> getSetInstruments();

private:
  CThostFtdcTraderApi* pUserApi;
  // �Ự����
  int	 frontId;	//ǰ�ñ��
  int	 sessionId;	//�Ự���
  char orderRef[13];

  set<string> instrumentsIds;

  vector<CThostFtdcOrderField*> orderList;
  vector<CThostFtdcTradeField*> tradeList;

};

#endif
