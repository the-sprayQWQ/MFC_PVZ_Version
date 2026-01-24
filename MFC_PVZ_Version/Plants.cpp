// Plants.cpp: 实现文件
//

#include "pch.h"
#include "MFC_PVZ_Version.h"
#include "afxdialogex.h"
#include "Plants.h"
#include "Global.h"
#include "./module/manage/pvzManager.h"


// Plants 对话框

IMPLEMENT_DYNAMIC(Plants, CDialogEx)

Plants::Plants(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Plants::~Plants()
{
}

void Plants::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Plants, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Plants::SetSun)
	ON_BN_CLICKED(IDC_BUTTON2, &Plants::AddZombies)
	ON_BN_CLICKED(IDC_COOLDOWN, &Plants::Cooldown)
	ON_BN_CLICKED(IDC_AUTOCOLLECT, &Plants::AutoCollect)
	ON_BN_CLICKED(IDC_PEADAMAGE, &Plants::PeaDamage)
	ON_BN_CLICKED(IDC_NOPAUSE, &Plants::NoPause)
	ON_BN_CLICKED(IDC_BUTTON3, &Plants::GetProps)
	ON_BN_CLICKED(IDC_PLANTSPEED, &Plants::PlantSpeed)
	ON_BN_CLICKED(IDC_BUTTON4, &Plants::SetPlant)
	ON_BN_CLICKED(IDC_FLOWEREAT, &Plants::FlowerEat)
	ON_BN_CLICKED(IDC_BUTTON5, &Plants::ChangePlantColor)
	ON_BN_CLICKED(IDC_BUTTON6, &Plants::RestorePlantColor)
	ON_BN_CLICKED(IDC_CHANGEZOMBIE, &Plants::ChangeZombie)
	ON_BN_CLICKED(IDC_CHANGEPEA, &Plants::ChangePea)
	ON_BN_CLICKED(IDC_CHANGENUT, &Plants::ChangeNut)
	ON_BN_CLICKED(IDC_NOCRATER, &Plants::NoCrater)
	ON_BN_CLICKED(IDC_INFINITYFREEZE, &Plants::InfinityFreeze)
	ON_BN_CLICKED(IDC_FLOWERATTCK, &Plants::FlowerAttck)
	ON_BN_CLICKED(IDC_MINEETIME, &Plants::MineeTime)
	ON_BN_CLICKED(IDC_INSTANTEXPLOSION, &Plants::InstantExplosion)
	ON_BN_CLICKED(IDC_ASHPLANT, &Plants::AshPlant)
	ON_BN_CLICKED(IDC_CHANGEPLANTS, &Plants::ChangePlant)
	ON_BN_CLICKED(IDC_MUSHROOMAWAKENING, &Plants::MushroomAwakening)
	ON_BN_CLICKED(IDC_CHANGEBUTTER, &Plants::ChangeButter)
	ON_BN_CLICKED(IDC_BUTTON7, &Plants::ChangeLevel)
	ON_BN_CLICKED(IDC_PLANTINGZOMBIES, &Plants::PlantingZombies)
	ON_BN_CLICKED(IDC_BUTTON8, &Plants::AllEnchant)

	ON_BN_CLICKED(IDC_ALLATTCK, &Plants::AllAttck)
	ON_BN_CLICKED(IDC_INFINITYZOMBIE, &Plants::InfinityZombie)
	ON_BN_CLICKED(IDC_PAUSESPAWN, &Plants::PauseSpawn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REDUCEHEALTH, &Plants::ReduceHealth)
	ON_BN_CLICKED(IDC_INSTANTBURN, &Plants::InstantBurn)
	ON_BN_CLICKED(IDC_ALLBURN, &Plants::AllBurn)
	ON_BN_CLICKED(IDC_COLUMNPLANT, &Plants::ColumnPlant)
	ON_BN_CLICKED(IDC_INTERCROPPING, &Plants::InterCropping)
	ON_BN_CLICKED(IDC_ALLEAT, &Plants::AllEat)
	ON_BN_CLICKED(IDC_ALLSTATUSKILL, &Plants::AllStatusKill)
	ON_BN_CLICKED(IDC_ALLNOMOVE, &Plants::AllNoMove)
END_MESSAGE_MAP()


// Plants 消息处理程序

BOOL Plants::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (VersionResult == 0) {
		SetWindowText(L"植物大战僵尸辅助 - 中文版/原版");
	}
	else if(VersionResult == 1) {
		SetWindowText(L"植物大战僵尸辅助 - Steam年度版");
	}
	else if(VersionResult == 2) {
		SetWindowText(L"植物大战僵尸辅助 - 年度版");
	}
	else {
		SetWindowText(L"植物大战僵尸辅助 - 未知版本");
	}

	::SendMessage(GetDlgItem(IDC_EDIT1)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"红 (0-255)");

	::SendMessage(GetDlgItem(IDC_EDIT2)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"绿 (0-255)");

	::SendMessage(GetDlgItem(IDC_EDIT3)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"蓝 (0-255)");

	::SendMessage(GetDlgItem(IDC_EDIT4)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物列");

	::SendMessage(GetDlgItem(IDC_EDIT5)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物行");

	::SendMessage(GetDlgItem(IDC_EDIT6)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物ID");

	::SendMessage(GetDlgItem(IDC_EDIT7)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸行数");

	::SendMessage(GetDlgItem(IDC_EDIT8)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸ID");

	::SendMessage(GetDlgItem(IDC_EDIT9)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"道具ID");

	::SendMessage(GetDlgItem(IDC_EDIT10)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"格子位置（1-x）");

	::SendMessage(GetDlgItem(IDC_EDIT11)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物ID");

	::SendMessage(GetDlgItem(IDC_EDIT12)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"关卡数");

	::SendMessage(GetDlgItem(IDC_EDIT13)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸列");

	::SendMessage(GetDlgItem(IDC_EDIT14)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸行");

	::SendMessage(GetDlgItem(IDC_EDIT15)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸种类");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Plants::SetSun()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.system.SetSunlight(9999);
}

void Plants::AddZombies()
{
	// TODO: 在此添加控件通知处理程序代码
	int Row = GetDlgItemInt(IDC_EDIT7, NULL, FALSE);
	int zType = GetDlgItemInt(IDC_EDIT8, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.zombies.AddZombies(Row, zType);
}

void Plants::Cooldown()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_COOLDOWN))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.system.EnableNoCooldown();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.system.DisableNoCooldown();
	}
}

void Plants::AutoCollect()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_AUTOCOLLECT))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.system.EnableAutoCollect();
	}
	else { 
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.system.DisableAutoCollect();
	}
}

void Plants::PeaDamage()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_PEADAMAGE))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.plant.EnablePeaDamage();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.plant.DisablePeaDamage();
	}
}

void Plants::NoPause()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_NOPAUSE))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.system.EnableNoPause();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.system.DisableNoPause();
	}
}

void Plants::GetProps()
{
	// TODO: 在此添加控件通知处理程序代码
	int zType = GetDlgItemInt(IDC_EDIT9, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.system.GetProps(zType);
}

void Plants::PlantSpeed()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_PLANTSPEED))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.plant.EnablePlantSpeed();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.plant.DisablePlantSpeed();
	}
}

void Plants::SetPlant()
{
	// TODO: 在此添加控件通知处理程序代码
	int Column = GetDlgItemInt(IDC_EDIT4, NULL, FALSE);
	int Row = GetDlgItemInt(IDC_EDIT5, NULL, FALSE);
	int pType = GetDlgItemInt(IDC_EDIT6, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.plant.SetPlant(Column, Row, pType);
}

void Plants::FlowerEat()
{
	// TODO: 在此添加控件通知处理程序代码

	int state = ((CButton*)GetDlgItem(IDC_FLOWEREAT))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.plant.EnableFlowerEat();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.plant.DisableFlowerEat();
	}
}

void Plants::ChangePlantColor()
{
	// TODO: 在此添加控件通知处理程序代码
	int Red = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);
	int Green = GetDlgItemInt(IDC_EDIT2, NULL, FALSE);
	int Blue = GetDlgItemInt(IDC_EDIT3, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.plant.ChangePlantColor(Red, Green, Blue);
}

void Plants::RestorePlantColor()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.plant.restorePlantColor();
}


void Plants::ChangeZombie()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGEZOMBIE))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.zombies.EnableChangeZombie(0,0);
	}
	else {
		pvzManager pvzManager;
		pvzManager.zombies.DisableChangeZombie();
	}
}

void Plants::ChangePea()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGEPEA))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableChangePea(1);
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableChangePea();
	}
}

void Plants::ChangeNut()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGENUT))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableChangeNut();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableChangeNut();
	}
}

void Plants::NoCrater()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_NOCRATER))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableNoCrater();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableNoCrater();
	}
}

void Plants::InfinityFreeze()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_INFINITYFREEZE))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableInfinityFreeze();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableInfinityFreeze();
	}
}

void Plants::FlowerAttck()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_FLOWERATTCK))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableFlowerAttck();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableFlowerAttck();
	}
}

void Plants::MineeTime()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_MINEETIME))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableMineeTime();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableMineeTime();
	}
}

void Plants::InstantExplosion()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_INSTANTEXPLOSION))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableInstantExplosion();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableInstantExplosion();
	}
}

void Plants::AshPlant()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_ASHPLANT))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableAshPlant();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableAshPlant();
	}
}

void Plants::ChangePlant()
{
	// TODO: 在此添加控件通知处理程序代码
	int plaidPos = GetDlgItemInt(IDC_EDIT10, NULL, FALSE);
	int plantType = GetDlgItemInt(IDC_EDIT11, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.plant.ChangePlant(plaidPos, plantType);

}

void Plants::MushroomAwakening()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_MUSHROOMAWAKENING))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableMushroomAwakening();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableMushroomAwakening();
	}
}

void Plants::ChangeButter()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGEBUTTER))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableChangeButter();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableChangeButter();
	}
}

void Plants::ChangeLevel()
{
	// TODO: 在此添加控件通知处理程序代码
	int Level = GetDlgItemInt(IDC_EDIT12, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.system.ChangeLevel(Level);
}

void Plants::PlantingZombies()
{
	// TODO: 在此添加控件通知处理程序代码
	int column = GetDlgItemInt(IDC_EDIT13, NULL, FALSE);
	int row = GetDlgItemInt(IDC_EDIT14, NULL, FALSE);
	int zType = GetDlgItemInt(IDC_EDIT15, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.zombies.SetZombies(column, row, zType);
}


void Plants::AllEnchant()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.plant.AllEnchant();
}

void Plants::AllAttck()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_ALLATTCK))->GetCheck();
	if (state == 1) {
		SetTimer(1, 1, NULL);
	}
	else {
		KillTimer(1);
		
	}
}

void Plants::InfinityZombie()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_INFINITYZOMBIE))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.zombies.EnableInfinityZombies();
	}
	else {
		pvzManager pvzManager;
		pvzManager.zombies.DisableInfinityZombies();
	}
}

void Plants::PauseSpawn()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_PAUSESPAWN))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.zombies.EnablePauseSpawn();
	}
	else {
		pvzManager pvzManager;
		pvzManager.zombies.DisablePauseSpawn();
	}
}

void Plants::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pvzManager pvzManager;
	if (nIDEvent == 1) {
		
		pvzManager.zombies.AllAttack();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void Plants::ReduceHealth()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.system.ReduceHealth();
}

void Plants::InstantBurn()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_INSTANTBURN))->GetCheck();
	if(state == 1){
		pvzManager pvzManager;
		pvzManager.plant.EnableInstantBurn();
	}else{
		pvzManager pvzManager;
		pvzManager.plant.DisableInstantBurn();
	}
}

void Plants::AllBurn()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_ALLBURN))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableAllBurn();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableAllBurn();
	}
}

void Plants::ColumnPlant()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_COLUMNPLANT))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.system.EnableColumnPlant();
	}
	else {
		pvzManager pvzManager;
		pvzManager.system.DisableColumnPlant();
	}
}

void Plants::InterCropping()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_INTERCROPPING))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.system.EnableInterCropping();
	}
	else {
		pvzManager pvzManager;
		pvzManager.system.DisableInterCropping();
	}
}

void Plants::AllEat()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_ALLEAT))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.plant.EnableAllEat();
	}
	else {
		pvzManager pvzManager;
		pvzManager.plant.DisableAllEat();
	}
}

void Plants::AllStatusKill()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_ALLSTATUSKILL))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.system.EnableAllStatusKill();
	}
	else {
		pvzManager pvzManager;
		pvzManager.system.DisableAllStatusKill();
	}
}

void Plants::AllNoMove()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_ALLNOMOVE))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.system.EnableAllNoMove();
	}
	else {
		pvzManager pvzManager;
		pvzManager.system.DisableAllNoMove();
	}
}
