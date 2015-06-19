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
 *			- Data for iMac13,2 and MacBookPro9,2 added (PikerAlpha, October 2013).
 *			- Typo in SMB_BOARD_PRODUCT for iMac12,n fixed (PikerAlpha, April 2013).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 *			- 4D3K for iMac12,n SMB_BOARD_PRODUCT typos.
 */


#if TARGET_MODEL & IMAC															// 1
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"iMac"

	#if (TARGET_MODEL == IMAC_111)
		#define SMB_BIOS_VERSION	"IM111.88Z.0034.B00.0910301727"
		#define SMB_PRODUCT_NAME	"iMac11,1"
		#define SMB_BOARD_PRODUCT	"Mac-F2268DAE"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '1', ',', '1' }
	#elif (TARGET_MODEL == IMAC_121)
		#define SMB_BIOS_VERSION	"IM121.88Z.0047.B1D.1110171110"
		#define SMB_PRODUCT_NAME	"iMac12,1"
		#define SMB_BOARD_PRODUCT	"Mac-942B5BF58194151B"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '2', ',', '1' }
	#elif (TARGET_MODEL == IMAC_122)
		#define SMB_BIOS_VERSION	"IM121.88Z.0047.B1D.1110171110"
		#define SMB_PRODUCT_NAME	"iMac12,2"
		#define SMB_BOARD_PRODUCT	"Mac-942B59F58194171B"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '2', ',', '2' }
	#elif (TARGET_MODEL == IMAC_131)
		#define SMB_BIOS_VERSION	"IM131.88Z.00CE.B00.1203281326"
		#define SMB_PRODUCT_NAME	"iMac13,1"
		#define SMB_BOARD_PRODUCT	"Mac-00BE6ED71E35EB86"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '3', ',', '1' }
	#elif (TARGET_MODEL == IMAC_132)
		#define SMB_BIOS_VERSION	"IM131.88Z.00CE.B00.1203281326"
		#define SMB_PRODUCT_NAME	"iMac13,2"
		#define SMB_BOARD_PRODUCT	"Mac-FC02E91DDD3FA6A4"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '3', ',', '2' }
	#elif (TARGET_MODEL == IMAC_141)
		#define SMB_BIOS_VERSION	"IM141.88Z.0118.B00.1309031248"
		#define SMB_PRODUCT_NAME	"iMac14,1"
		#define SMB_BOARD_PRODUCT	"Mac-031B6874CF7F642A"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '1' }
	#elif (TARGET_MODEL == IMAC_142)
		#define SMB_BIOS_VERSION	"IM141.88Z.0118.B00.1309031249"
		#define SMB_PRODUCT_NAME	"iMac14,2"
		#define SMB_BOARD_PRODUCT	"Mac-27ADBB7B4CEE8E61"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '2' }
	#elif (TARGET_MODEL == IMAC_143)
		#define SMB_BIOS_VERSION	"IM143.88Z.0118.B00.1309031249"
		#define SMB_PRODUCT_NAME	"iMac14,3"
		#define SMB_BOARD_PRODUCT	"Mac-77EB7D7DAF985301"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '3' }
	#elif (TARGET_MODEL == IMAC_144)
		#define SMB_BIOS_VERSION	"IM144.88Z.0179.B03.1405241029"
		#define SMB_PRODUCT_NAME	"iMac14,4"
		#define SMB_BOARD_PRODUCT	"Mac-81E3E92DD6088272"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '4' }
	#elif (TARGET_MODEL == IMAC_152)
		// Intel Core i7-4790K @ 4 GHz
		#define SMB_BIOS_VERSION	"IM151.88Z.0207.B00.1409291931"
		#define SMB_PRODUCT_NAME	"iMac15,2"
		#define SMB_BOARD_PRODUCT	"Mac-FA842E06C61E91C5"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '5', ',', '2' }
	#else // Defaults to iMac 15,1
		// Intel Core i5-4690 @ 3.50 GHz
		#define SMB_BIOS_VERSION	"IM151.88Z.0207.B00.1409291931"
		#define SMB_PRODUCT_NAME	"iMac15,1"
		#define SMB_BOARD_PRODUCT	"Mac-42FD25EABCABB274"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '5', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK														// 2
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBook"

	#if (TARGET_MODEL == MACBOOK_41)
		#define SMB_BIOS_VERSION	"MB41.88Z.0073.B00.0809221748"
		#define SMB_PRODUCT_NAME	"MacBook4,1"
		#define SMB_BOARD_PRODUCT	"Mac-F42D89C8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', '4', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_81)
		// Intel Core M-5Y31 @ 1.10 GHz (2 cores, 4 threads)
		#define SMB_BIOS_VERSION	"MB81.88Z.0164.B02.1503241252"
		#define SMB_PRODUCT_NAME	"MacBook8,1"
		#define SMB_BOARD_PRODUCT	"Mac-BE0E8AC46FE800CC"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', '8', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK_AIR													// 4
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBookAir"

	#if (TARGET_MODEL == MACBOOK_AIR_41)
		// Intel Core i5-2467M @ 1.6GHz (2 cores - 4 threads)
		// Intel Core i7-2677M @ 1.8GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA41.88Z.0077.B08.1109011050"
		#define SMB_PRODUCT_NAME	"MacBookAir4,1"
		#define SMB_BOARD_PRODUCT	"Mac-C08A6BB70A942AC2"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '4', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_AIR_42)
		// Intel Core i5-2557M @ 1.7GHz (2 cores - 4 threads)
		// Intel Core i7-2677M @ 1.8GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA41.88Z.0077.B08.1109011050"
		#define SMB_PRODUCT_NAME	"MacBookAir4,2"
		#define SMB_BOARD_PRODUCT	"Mac-742912EFDBEE19B3"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '4', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_AIR_61)
		// Intel Core i5-4250U @ 1.30 GHz (2 cores - 4 threads)
		// Intel Core i7-4650U @ 1.70 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA61.88Z.0099.B12.1405241030"
		#define SMB_PRODUCT_NAME	"MacBookAir6,1"
		#define SMB_BOARD_PRODUCT	"Mac-35C1E88140C3E6CF"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '6', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_AIR_62)
		// Intel Core i5-4250U @ 1.30 GHz (2 cores - 4 threads)
		// Intel Core i7-4650U @ 1.70 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA61.88Z.0099.B12.1405241030"
		#define SMB_PRODUCT_NAME	"MacBookAir6,2"
		#define SMB_BOARD_PRODUCT	"Mac-7DF21CB3ED6977E5"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '6', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_AIR_71)
		// Intel Core i5-5250U @ 1.60 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA71.88Z.0166.B00.1502131457"
		#define SMB_PRODUCT_NAME	"MacBookAir7,1"
		#define SMB_BOARD_PRODUCT	"Mac-9F18E312C5C2BF0B"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '7', ',', '1' }
	#else // Defaults to MacBookAir7,2
		// Intel Core i5-5250U @ 1.60 GHz (2 cores - 4 threads)
		// Intel Core i7-5650U @ 2.20 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA71.88Z.0166.B00.1502131457"
		#define SMB_PRODUCT_NAME	"MacBookAir7,2"
		#define SMB_BOARD_PRODUCT	"Mac-937CB26E2E02BB01"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '7', ',', '2' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK_PRO													// 8
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBookPro"

	#if(TARGET_MODEL == MACBOOK_PRO_61)
		#define SMB_BIOS_VERSION	"MBP61.88Z.0057.B0C.1007261552"
		#define SMB_PRODUCT_NAME	"MacBookPro6,1"
		#define SMB_BOARD_PRODUCT	"Mac-F22589C8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '6', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_81)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B27.1201241646"
		#define SMB_PRODUCT_NAME	"MacBookPro8,1"
		#define SMB_BOARD_PRODUCT	"Mac-94245B3640C91C81"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_82)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B27.1201241646"
		#define SMB_PRODUCT_NAME	"MacBookPro8,2"
		#define SMB_BOARD_PRODUCT	"Mac-94245A3940C91C80"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_83)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B27.1201241646"
		#define SMB_PRODUCT_NAME	"MacBookPro8,3"
		#define SMB_BOARD_PRODUCT	"Mac-942459F5819B171B"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '3' }
	#elif (TARGET_MODEL == MACBOOK_PRO_91)
		// Intel Core i7-3820QM @ 2.70 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP91.88Z.00D3.B02.1203281326"
		#define SMB_PRODUCT_NAME	"MacBookPro9,1"
		#define SMB_BOARD_PRODUCT	"Mac-4B7AC7E43945597E"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '9', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_92)
		// Intel Core i7-3820QM @ 2.70 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP91.88Z.00D3.B02.1203281326"
		#define SMB_PRODUCT_NAME	"MacBookPro9,2"
		#define SMB_BOARD_PRODUCT	"Mac-6F01561E16C75D06"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '9', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_101)
		// Intel Core i7-3635QM @ 2.40 GHz - 4 cores / 8 threads.
		// Intel Core i7-3740QM @ 2.70 GHz - 4 cores / 8 threads.
		// Intel Core i7-3840QM @ 2.80 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP101.88Z.00EE.B03.1212211437"
		#define SMB_PRODUCT_NAME	"MacBookPro10,1"
		#define SMB_BOARD_PRODUCT	"Mac-C3EC7CD22292981F"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '0', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_102)
		// Intel Core i5-3230QM @ 2.60 GHz - 2 cores / 4 threads.
		// Intel Core i7-3540QM @ 3.00 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP102.88Z.0106.B03.1211161133"
		#define SMB_PRODUCT_NAME	"MacBookPro10,2"
		#define SMB_BOARD_PRODUCT	"Mac-AFD8A9D944EA4843"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '0', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_111)
		// Intel Core i5-4258U @ 2.40 GHz - 2 cores / 4 threads.
		// Intel Core i5-4288U @ 2.60 GHz - 2 cores / 4 threads.
		// Intel Core i7-4558U @ 2.80 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP111.88Z.0138.B07.1402121134"
		#define SMB_PRODUCT_NAME	"MacBookPro11,1"
		#define SMB_BOARD_PRODUCT	"Mac-189A3D4F975D5FFC"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_112)
		// Intel Core i7-4750HQ @ 2.00 GHz - 4 cores / 8 threads.
		// Intel Core i7-4950HQ @ 2.40 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP112.88Z.0138.B02.1310181745"
		#define SMB_PRODUCT_NAME	"MacBookPro11,2"
		#define SMB_BOARD_PRODUCT	"Mac-3CBD00234E554E41"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_113)
		// Intel Core i7-4850HQ @ 2.30 GHz - 4 cores / 8 threads.
		// Intel Core i7-4960HQ @ 2.60 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP112.88Z.0138.B08.1406081756"
		#define SMB_PRODUCT_NAME	"MacBookPro11,3"
		#define SMB_BOARD_PRODUCT	"Mac-2BD1B31983FE1663"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '2', ',', '1' }
	#else
		// Intel Core i5-5257U @ 2.70 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP121.88Z.0167.B00.1502132146"
		#define SMB_PRODUCT_NAME	"MacBookPro12,1"
		#define SMB_BOARD_PRODUCT	"Mac-E43C1C25D4880AD6"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '2', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACMINI														// 16
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"Macmini"

	#if (TARGET_MODEL == MACMINI_41)
		// Intel Core P8800 @ 2.4/2.66 GHz (2 cores - 2 threads)
		#define SMB_BIOS_VERSION	"MM41.88Z.0042.B03.1111072100"
		#define SMB_PRODUCT_NAME	"Macmini4,1"
		#define SMB_BOARD_PRODUCT	"Mac-F2208EC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '4', ',', '1' }
	#elif (TARGET_MODEL == MACMINI_51)
		// Intel Core i5-2415M @ 2.3 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B10.1201241549"
		#define SMB_PRODUCT_NAME	"Macmini5,1"
		#define SMB_BOARD_PRODUCT	"Mac-8ED6AF5B48C039E1"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '1' }
	#elif (TARGET_MODEL == MACMINI_52)
		// Intel Core i5-2520M @ 2.5GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B10.1201241549"
		#define SMB_PRODUCT_NAME	"Macmini5,2"
		#define SMB_BOARD_PRODUCT	"Mac-4BC72D62AD45599E"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '2' }
	#elif (TARGET_MODEL == MACMINI_53)
		// Intel Core i7-2635QM @ 2.0GHz (4 cores - 8 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B10.1201241549"
		#define SMB_PRODUCT_NAME	"Macmini5,3"
		#define SMB_BOARD_PRODUCT	"Mac-7BA5B2794B2CDB12"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '3' }
	#elif (TARGET_MODEL == MACMINI_61)
		// Intel Core i5-3210M @ 2.50 GH (2 cores - 4 theeads)
		#define SMB_BIOS_VERSION	"MM61.88Z.0106.B03.1211161202"
		#define SMB_PRODUCT_NAME	"Macmini6,1"
		#define SMB_BOARD_PRODUCT	"Mac-031AEE4D24BFF0B1"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '6', ',', '1' }
	#elif (TARGET_MODEL == MACMINI_62)
		// Intel Core i7-3615QM @ 2.30 GHz (4 cores - 8 threads)
		#define SMB_BIOS_VERSION	"MM61.88Z.0106.B03.1211161202"
		#define SMB_PRODUCT_NAME	"Macmini6,2"
		#define SMB_BOARD_PRODUCT	"Mac-F65AE981FFA204ED"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '6', ',', '2' }
	#else // Defaults to Macmini7,1
		#define SMB_BIOS_VERSION	"MM71.88Z.0220.B00.1409291751"
		#define SMB_PRODUCT_NAME	"Macmini7,1"
		#define SMB_BOARD_PRODUCT	"Mac-35C5E08120C7EEAF"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '7', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACPRO														// 32
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacPro"

	#if (TARGET_MODEL == MACPRO_31)
		#define SMB_BIOS_VERSION	"MP31.88Z.006C.B05.0802291410"
		#define SMB_PRODUCT_NAME	"MacPro3,1"
		#define SMB_BOARD_PRODUCT	"Mac-F4208DC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '3', ',', '1' }
	#elif (TARGET_MODEL == MACPRO_41)
		#define SMB_BIOS_VERSION	"MP41.88Z.0081.B04.0903051113"
		#define SMB_PRODUCT_NAME	"MacPro4,1"
		#define SMB_BOARD_PRODUCT	"Mac-F221BEC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '4', ',', '1' }
	#elif (TARGET_MODEL == MACPRO_51)
		#define SMB_BIOS_VERSION	"MP51.88Z.007F.B03.1010071432"
		#define SMB_PRODUCT_NAME	"MacPro5,1"
		#define SMB_BOARD_PRODUCT	"Mac-F221BEC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '5', ',', '1' }
	#else // Defaults to MacPro6,1
		#define SMB_BIOS_VERSION	"MP61.88Z.0116.B04.1312061508"
		#define SMB_PRODUCT_NAME	"MacPro6,1"
		#define SMB_BOARD_PRODUCT	"Mac-F60DEB81FF30ACF6"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '6', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif