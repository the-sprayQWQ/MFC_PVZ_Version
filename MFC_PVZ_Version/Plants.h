#pragma once
#include "afxdialogex.h"


// Plants 对话框

class Plants : public CDialogEx
{
	DECLARE_DYNAMIC(Plants)

public:
	Plants(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Plants();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void SetSun();
	afx_msg void AddZombies();
	afx_msg void Cooldown();
	afx_msg void AutoCollect();
	afx_msg void PeaDamage();
	afx_msg void NoPause();
	afx_msg void GetProps();
	afx_msg void PlantSpeed();
	afx_msg void SetPlant();
	afx_msg void FlowerEat();
	afx_msg void ChangePlantColor();
	afx_msg void RestorePlantColor();
	afx_msg void ChangeZombie();
	afx_msg void ChangePea();
	afx_msg void ChangeNut();
	afx_msg void NoCrater();
	afx_msg void InfinityFreeze();
	afx_msg void FlowerAttck();
	afx_msg void MineeTime();
	afx_msg void InstantExplosion();
	afx_msg void AshPlant();
	afx_msg void ChangePlant();
	afx_msg void MushroomAwakening();
	afx_msg void ChangeButter();
	afx_msg void ChangeLevel();
	afx_msg void PlantingZombies();
	afx_msg void AllEnchant();
	afx_msg void AllAttck();
	afx_msg void InfinityZombie();
	afx_msg void PauseSpawn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void ReduceHealth();
	afx_msg void InstantBurn();
	afx_msg void AllBurn();
	afx_msg void ColumnPlant();
};
