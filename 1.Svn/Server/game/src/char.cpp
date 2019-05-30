//Find
	tab.skill_group	= m_points.skill_group;
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	tab.envanter 		= Inven_Point();
#endif

//Find
	pack.points[POINT_MAX_STAMINA] = GetMaxStamina();
	
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	pack.points[POINT_INVEN]		= Inven_Point();
#endif

//Find
	SetGold(t->gold);
	
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	Set_Inventory_Point(t->envanter);
#endif

//Find
	long lSPRecovery = GetPoint(POINT_SP_RECOVERY);

///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	long envanterim = Inven_Point();
#endif

//Find
	SetPoint(POINT_PC_BANG_DROP_BONUS, 0);

///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	SetPoint(POINT_INVEN, envanterim);
#endif

//Find
		case POINT_MAX_STAMINA:
			SetMaxStamina(GetMaxStamina() + amount);
			val = GetMaxStamina();
			break;
	
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
		case POINT_INVEN:
			{
				const int64_t Envantertoplami = static_cast<int64_t>(Inven_Point()) + static_cast<int64_t>(amount);
				if (Envantertoplami > INVENTORY_LOCK_COVER_COUNT)
				{
					sys_err("[POINT_INVEN ERROR]");
					return;
				}
				Set_Inventory_Point(Inven_Point() + amount);
				val = Inven_Point();
			}
			break;
#endif

///Add end of cpp
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
bool CHARACTER::Update_Inven()
{
	std::vector<int> needkeys;
	for (int i = 2; i <= (INVENTORY_LOCKED_PAGE_COUNT*3)+1; i++)
		for (int j = 0; j < 3; j++)
			needkeys.push_back(i);	
	int needkey = needkeys[Inven_Point()];
	if (CountSpecifyItem(INVENTORY_OPEN_KEY_VNUM) >= needkey)
		RemoveSpecifyItem(INVENTORY_OPEN_KEY_VNUM, needkey);
	else
	{
		int nekadar = needkey - CountSpecifyItem(INVENTORY_OPEN_KEY_VNUM);
		ChatPacket(CHAT_TYPE_COMMAND, "ExInvenItemUseMsg %d", nekadar);
		return false;
	}
	PointChange(POINT_INVEN, 1, false);
	UpdatePacket();		
	return true;
}
#endif