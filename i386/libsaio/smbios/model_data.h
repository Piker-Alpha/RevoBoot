/*
 * The first SMBIOS patcher was developped by 'mackerintel' in 2008, which was ripped
 * apart and completely rewritten by Master Chief for Revolution in 2009.
 *
 * Then Samantha AKA DHP/RevoGirl took control of the project, which she maintained for
 * a couple of years.  Sam did an amazing job, up until her sad passing. Totally in line
 * with her uplifting spirit and work ethics.
 *
 * Now it is time to say goodbye to some of the legacy code.  Something I will do with
 * the help of her notes, but not everything is written in stone.  Meaning that I will
 * have to experiment and improvise.  Hopefully achieving the same goals that she had
 * in mind for you.  Wish me luck.
 *
 * Updates:
 *
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- Complete rewrite / overhaul by DHP in Februari 2011.
 *			- Coding style changes by DHP in Februari 2011.
 *			- Model data stripped and simplified (PikerAlpha, October 2012).
 *			- EFI/SMBIOS data logic moved to preprocessor code (PikerAlpha, October 2012).
 *			- SMB_PRODUCT_NAME renamed/moved over from settings.h (PikerAlpha, October 2012).
 *			- EFI_MODEL_NAME renamed/moved over from settings.h (PikerAlpha, October 2012).
 *			- Data for new MacBookPro and Macmini added (PikerAlpha, October 2012).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 */


#if TARGET_MODEL & IMAC															// 1
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"Mac"

	#if (TARGET_MODEL == IMAC_131)
		// Intel Core i7-3770 @ 3.40 GHz - 4 Cores / 8 Threads.
		#define SMB_BIOS_VERSION	"IM131.88Z.00CE.B00.1203281326"
		#define SMB_PRODUCT_NAME	"iMac13,1"
		#define SMB_BOARD_PRODUCT	"Mac-FC02E91DDD3FA6A4"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '3', ',', '1' }
	#elif (TARGET_MODEL == IMAC_122)
		#define SMB_BIOS_VERSION	"IM121.88Z.0047.B1D.1110171110"
		#define SMB_PRODUCT_NAME	"iMac12,2"
		#define SMB_BOARD_PRODUCT	"Mac-942B5BF58194151B"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '2', ',', '2' }
	#elif (TARGET_MODEL == IMAC_111)
		#define SMB_BIOS_VERSION	"IM111.88Z.0034.B00.0910301727"
		#define SMB_PRODUCT_NAME	"iMac11,1"
		#define SMB_BOARD_PRODUCT	"Mac-F2268DAE"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '1', ',', '1' }
	#else // Defaults to iMac12,1
		#define SMB_BIOS_VERSION	"IM121.88Z.0047.B1D.1110171110"
		#define SMB_PRODUCT_NAME	"iMac12,1"
		#define SMB_BOARD_PRODUCT	"Mac-942B59F58194171B"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '2', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK														// 2
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBook"

	#define SMB_BIOS_VERSION	"MB41.88Z.0073.B00.0809221748"
	#define SMB_PRODUCT_NAME	"MacBook4,1"
	#define SMB_BOARD_PRODUCT	"Mac-F42D89C8"
	#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', '4', ',', '1' }
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK_AIR													// 4
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBookAir"

	#if (TARGET_MODEL == MACBOOK_AIR_42)
		// Intel Core i5-2557M @ 1.7GHz (2 cores - 4 threads)
		// Intel Core i7-2677M @ 1.8GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA41.88Z.0077.B08.1109011050"
		#define SMB_PRODUCT_NAME	"MacBookAir4,2"
		#define SMB_BOARD_PRODUCT	"Mac-742912EFDBEE19B3"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '4', ',', '2' }
	#else // Defaults to MacBookAir4,1
		// Intel Core i5-2467M @ 1.6GHz (2 cores - 4 threads)
		// Intel Core i7-2677M @ 1.8GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA41.88Z.0077.B08.1109011050"
		#define SMB_PRODUCT_NAME	"MacBookAir4,1"
		#define SMB_BOARD_PRODUCT	"Mac-C08A6BB70A942AC2"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '4', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK_PRO													// 8
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBookPro"

	#if (TARGET_MODEL == MACBOOK_PRO_102)
		// Intel Core i7-3520QM @ 2.90 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP102.88Z.00FE.B00.1207181057"
		#define SMB_PRODUCT_NAME	"MacBookPro10,2"
		#define SMB_BOARD_PRODUCT	"Mac-AFD8A9D944EA4843"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '0', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_101)
		// Intel Core i7-3720QM @ 2.60 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP101.88Z.00EE.B00.1205101839"
		#define SMB_PRODUCT_NAME	"MacBookPro10,1"
		#define SMB_BOARD_PRODUCT	"Mac-C3EC7CD22292981F"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '0', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_91)
		// Intel Core i7-3820QM @ 2.70 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP91.88Z.00D3.B00.1203211536"
		#define SMB_PRODUCT_NAME	"MacBookPro9,1"
		#define SMB_BOARD_PRODUCT	"Mac-4B7AC7E43945597E"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '9', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_83)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B24.1110141131"
		#define SMB_PRODUCT_NAME	"MacBookPro8,3"
		#define SMB_BOARD_PRODUCT	"Mac-942459F5819B171B"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '3' }
	#elif (TARGET_MODEL == MACBOOK_PRO_82)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B24.1110141131"
		#define SMB_PRODUCT_NAME	"MacBookPro8,2"
		#define SMB_BOARD_PRODUCT	"Mac-94245A3940C91C80"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_81)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B24.1110141131"
		#define SMB_PRODUCT_NAME	"MacBookPro8,1"
		#define SMB_BOARD_PRODUCT	"Mac-94245B3640C91C81"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '1' }
	#else (TARGET_MODEL == MACBOOK_PRO_61)
		#define SMB_BIOS_VERSION	"MBP61.88Z.0057.B0C.1007261552"
		#define SMB_PRODUCT_NAME	"MacBookPro6,1"
		#define SMB_BOARD_PRODUCT	"Mac-F22589C8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '6', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACMINI														// 16
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"Macmini"

	#if (TARGET_MODEL == MACMINI_62)
		// Intel Core i7-3615QM @ 2.30 GHz (4 cores - 8 threads)
		#define SMB_BIOS_VERSION	"MM61.88Z.0106.B00.1208091121"
		#define SMB_PRODUCT_NAME	"Macmini6,2"
		#define SMB_BOARD_PRODUCT	"Mac-F65AE981FFA204ED"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '6', ',', '2' }
	#elif (TARGET_MODEL == MACMINI_61)
		// Intel Core i5-3210M @ 2.50 GH (2 cores - 4 theeads)
		#define SMB_BIOS_VERSION	"MM61.88Z.0106.B00.1208091121"
		#define SMB_PRODUCT_NAME	"Macmini6,1"
		#define SMB_BOARD_PRODUCT	"Mac-031AEE4D24BFF0B1"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '6', ',', '1' }
	#elif (TARGET_MODEL == MACMINI_53)
		// Intel Core i7-2635QM @ 2.0GHz (4 cores - 8 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B10.1201241549"
		#define SMB_PRODUCT_NAME	"Macmini5,3"
		#define SMB_BOARD_PRODUCT	"Mac-7BA5B2794B2CDB12"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '3' }
	#elif (TARGET_MODEL == MACMINI_52)
		// Intel Core i5-2520M @ 2.5GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B10.1201241549"
		#define SMB_PRODUCT_NAME	"Macmini5,2"
		#define SMB_BOARD_PRODUCT	"Mac-4BC72D62AD45599E"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '2' }
	#else // Defaults to Macmini5,1
		// Intel Core i5-2415M @ 2.3 GHz (2 cores - 4 theeads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B10.1201241549"
		#define SMB_PRODUCT_NAME	"Macmini5,1"
		#define SMB_BOARD_PRODUCT	"Mac-8ED6AF5B48C039E1"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACPRO														// 32
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacPro"

	#if (TARGET_MODEL == MACPRO_51)
		#define SMB_BIOS_VERSION	"MP51.88Z.007F.B03.1010071432"
		#define SMB_PRODUCT_NAME	"MacPro5,1"
		#define SMB_BOARD_PRODUCT	"Mac-F221BEC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '5', ',', '1' }
	#elif (TARGET_MODEL == MACPRO_41)
		#define SMB_BIOS_VERSION	"MP41.88Z.0081.B04.0903051113"
		#define SMB_PRODUCT_NAME	"MacPro4,1"
		#define SMB_BOARD_PRODUCT	"Mac-F221BEC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '4', ',', '1' }
	#else // Defaults to MacPro3,1
		#define SMB_BIOS_VERSION	"MP31.88Z.006C.B05.0802291410"
		#define SMB_PRODUCT_NAME	"MacPro3,1"
		#define SMB_BOARD_PRODUCT	"Mac-F4208DC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '3', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif
