#include "mdspi.h"
using namespace std;


void CtpMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast) {
  IsErrorRspInfo(pRspInfo);
}

void CtpMdSpi::OnFrontDisconnected(int nReason) {
  cerr << " return | break..."
       << " reason=" << nReason << endl;
}

void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse) {
  cerr << " return | heart warming..."
       << " TimerLapse = " << nTimeLapse << endl;
}

void CtpMdSpi::OnFrontConnected() {
  cerr << " connect md ...success" << endl;
}


void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast) {
  if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin) {
    cerr << " on ret | login in succeed...current date:" << pRspUserLogin->TradingDay
         << endl;
  }
}

void CtpMdSpi::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  cerr << " on req |  submit market ...succeed" << endl;
}

void CtpMdSpi::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  cerr << " on req |  remove the market date...succeed" << endl;
}

void CtpMdSpi::OnRtnDepthMarketData(
    CThostFtdcDepthMarketDataField *pDepthMarketData) {
  string InstrumentID = pDepthMarketData->InstrumentID;
  cout<<InstrumentID<<endl;
  strToFile(InstrumentID);

/*
  cout << pDepthMarketData->InstrumentID << endl;
  cout << pDepthMarketData->TradingDay << endl;
  cout << pDepthMarketData->LastPrice << endl;
  cout << pDepthMarketData->Volume << endl;
  cout << pDepthMarketData->BidPrice1 << endl;
  cout << pDepthMarketData->AskPrice1 << endl;
  */
}

bool CtpMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
  bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (ret){
    cerr<<" on req | "<<pRspInfo->ErrorMsg<<endl;
  }
  return ret;
}
