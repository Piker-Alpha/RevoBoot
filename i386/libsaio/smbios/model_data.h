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
 *			- Model data stripped and simplified (Pike R. Alpha, October 2012).
 *			- EFI/SMBIOS data logic moved to preprocessor code (Pike R. Alpha, October 2012).
 *			- SMB_PRODUCT_NAME renamed/moved over from settings.h (Pike R. Alpha, October 2012).
 *			- EFI_MODEL_NAME renamed/moved over from settings.h (Pike R. Alpha, October 2012).
 *			- Data for new MacBookPro and Macmini added (Pike R. Alpha, October 2012).
 *			- Data for iMac13,2 and MacBookPro9,2 added (Pike R. Alpha, October 2013).
 *			- Typo in SMB_BOARD_PRODUCT for iMac12,n fixed (Pike R. Alpha, April 2013).
  *			- Data for new iMac18,x and MacBookPro14,x added (Pike R. Alpha, June 2017).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 *			- 4D3K for iMac12,n SMB_BOARD_PRODUCT typos.
 */


#if TARGET_MODEL & IMAC															// 1
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"iMac"

	#if (TARGET_MODEL == IMAC_111) // 27-inch, Late 2009
		// Intel Core i5-750 @ 2.66 GHz - 4 cores / 4 threads
		// Intel Core i7-860 @ 2.80 GHz - 4 cores / 8 threads
		// ATI Radeon HD 4850
		#define SMB_BIOS_VERSION	"IM111.88Z.0034.B12.1705021416"
		#define SMB_PRODUCT_NAME	"iMac11,1"
		#define SMB_BOARD_PRODUCT	"Mac-F2268DAE"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '1', ',', '1' }
	#elif (TARGET_MODEL == IMAC_121) // 21.5-inch, Mid 2011
		// Intel Core i3-2100 @ 3.10 GHz - 2 cores / 4 threads
		// Intel Core i5-2400S @ 2.50 GHz - 4 cores / 4 threads
		// Intel Core i5-2500S @ 2.70 GHz - 4 cores / 4 threads
		// Intel Core i7-2600S @ 2.80 GHz - 4 cores / 8 threads
		// AMD Radeon HD 6750M & AMD Radeon HD 6770M
		#define SMB_BIOS_VERSION	"IM121.88Z.0047.B33.1705101231"
		#define SMB_PRODUCT_NAME	"iMac12,1"
		#define SMB_BOARD_PRODUCT	"Mac-942B5BF58194151B"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '2', ',', '1' }
	#elif (TARGET_MODEL == IMAC_122) // 27-inch, Mid 2011
		// Intel Core i5-2400 @ 3.10 GHz - 4 cores / 4 threads
		// Intel Core i5-2500S @ 2.70 GHz - 4 cores / 4 threads
		// Intel Core i7-2600 @ 3.40 GHz - 4 cores / 8 threads
		// AMD Radeon HD 6770M & AMD Radeon HD 6970M
		#define SMB_BIOS_VERSION	"IM121.88Z.0047.B33.1705101231"
		#define SMB_PRODUCT_NAME	"iMac12,2"
		#define SMB_BOARD_PRODUCT	"Mac-942B59F58194171B"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '2', ',', '2' }
	#elif (TARGET_MODEL == IMAC_131) // 21.5-inch, Late 2012
		// Intel Core i5-3335S @ 2.70 GHz - 4 cores / 4 threads
		// Intel Core i5-3470S @ 2.90 GHz - 4 cores / 4 threads
		// Intel Core i7-3770S @ 3.10 GHz - 4 cores / 8 threads
		// NVIDIA GeForce GT 640M & NVIDIA GeForce GT 650M
		#define SMB_BIOS_VERSION	"IM131.88Z.010A.B1C.1705011311"
		#define SMB_PRODUCT_NAME	"iMac13,1"
		#define SMB_BOARD_PRODUCT	"Mac-00BE6ED71E35EB86"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '3', ',', '1' }
	#elif (TARGET_MODEL == IMAC_132) // 27-inch, Late 2012
		// Intel Core i5-3470S @ 2.9 GHz - 4 cores / 4 threads
		// Intel Core i5-3470 @ 3.2 GHz - 4 cores / 4 threads
		// Intel Core i7-3770 @ 3.4 GHz - 4 cores / 8 threads
		// NVIDIA GeForce GTX 660M, NVIDIA GeForce GTX 675MX & NVIDIA GeForce GTX 680MX
		#define SMB_BIOS_VERSION	"IM131.88Z.010A.B1C.1705011311"
		#define SMB_PRODUCT_NAME	"iMac13,2"
		#define SMB_BOARD_PRODUCT	"Mac-FC02E91DDD3FA6A4"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '3', ',', '2' }
	#elif (TARGET_MODEL == IMAC_133) // 21.5-inch, Early 2013 (Education)
		// Intel Core i3-3225 @ 3.30 GHz - 2 cores / 4 threads
		// Intel HD Graphics 4000
		#define SMB_BIOS_VERSION	"IM131.88Z.010A.B1C.1705011311"
		#define SMB_PRODUCT_NAME	"iMac13,3"
		#define SMB_BOARD_PRODUCT	"Mac-7DF2A3B5E5D671ED"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '3', ',', '3' }
	#elif (TARGET_MODEL == IMAC_141) // 21.5-inch, Late 2013
		// Intel Core i5-4570R @ 2.70 GHz - 4 cores / 4 threads
		// Intel Iris Pro Graphics 5200
		#define SMB_BIOS_VERSION	"IM141.88Z.0118.B46.1705011412"
		#define SMB_PRODUCT_NAME	"iMac14,1"
		#define SMB_BOARD_PRODUCT	"Mac-031B6874CF7F642A"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '1' }
	#elif (TARGET_MODEL == IMAC_142) // 27-inch, Late 2013
		// Intel Core i5-4570 @ 3.20 GHz - 4 cores / 4 threads
		// Intel Core i5-4670 @ 3.40 GHz - 4 cores / 4 threads
		// Intel Core i7-4771 @ 3.50 GHz - 4 cores / 8 threads
		// NVIDIA GeForce GT 755M, NVIDIA GeForce GTX 775M & NVIDIA GeForce GTX 780M
		#define SMB_BIOS_VERSION	"IM142.88Z.0118.B46.1705011513"
		#define SMB_PRODUCT_NAME	"iMac14,2"
		#define SMB_BOARD_PRODUCT	"Mac-27ADBB7B4CEE8E61"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '2' }
	#elif (TARGET_MODEL == IMAC_143) // 21.5-inch, Late 2013
		// Intel Core i5-4570S @ 2.80 GHz - 4 cores / 4 threads
		// Intel Core i7-4770S @ 3.10 GHz - 4 cores / 8 threads
		// NVIDIA GeForce GT 750M
		#define SMB_BIOS_VERSION	"IM143.88Z.0118.B13.1602221716"
		#define SMB_PRODUCT_NAME	"iMac14,3"
		#define SMB_BOARD_PRODUCT	"Mac-77EB7D7DAF985301"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '3' }
	#elif (TARGET_MODEL == IMAC_144) // 21.5-inch, Mid 2014
		// Intel Core i5-4260U @ 1.40 GHz - 2 cores / 4 threads
		// Intel HD Graphics 5000
		#define SMB_BIOS_VERSION	"IM144.88Z.0179.B30.1705011718"
		#define SMB_PRODUCT_NAME	"iMac14,4"
		#define SMB_BOARD_PRODUCT	"Mac-81E3E92DD6088272"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '4', ',', '4' }
	#elif (TARGET_MODEL == IMAC_151) // Retina 5K, 27-inch, Late 2014
		// Intel Core i5-4690 @ 3.50 GHz - 4 cores / 4 threads
		// Intel Core i7-4790K @ 4.00 GHz - 4 cores / 8 threads
		// AMD Radeon R9 M290X, AMD Radeon R9 M295X
		#define SMB_BIOS_VERSION	"IM151.88Z.0207.B26.1705011718"
		#define SMB_PRODUCT_NAME	"iMac15,1"
		#define SMB_BOARD_PRODUCT	"Mac-42FD25EABCABB274"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '5', ',', '1' }
	#elif (TARGET_MODEL == IMAC_152) // Retina 5K, 27-inch, Mid 2015
		// Intel Core i5-4590 @ 3.30 GHz - 4 cores / 4 threads
		// AMD Radeon R9 M290
		#define SMB_BIOS_VERSION	"IM151.88Z.0207.B26.1705011718"
		#define SMB_PRODUCT_NAME	"iMac15,2"
		#define SMB_BOARD_PRODUCT	"Mac-FA842E06C61E91C5"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '5', ',', '2' }
	#elif (TARGET_MODEL == IMAC_161) // 21.5-inch, Late 2015
		// Intel Core i5-5250U @ 1.60 GHz - 2 cores / 4 threads
		// Intel HD Graphics 6000
		#define SMB_BIOS_VERSION	"IM161.88Z.0207.B19.1705011046"
		#define SMB_PRODUCT_NAME	"iMac16,1"
		#define SMB_BOARD_PRODUCT	"Mac-A369DDC4E67F1C45"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '6', ',', '1' }
	#elif (TARGET_MODEL == IMAC_162) // Retina 5K, 21.5-inch, Late 2015
		// Intel Core i5-5575R @ 2.80 GHz - 4 cores / 4 threads
		// Intel Core i5-5675R @ 3.10 GHz - 4 cores / 4 threads
		// Intel Core i7-5775R @ 3.30 GHz - 4 cores / 8 threads
		// Intel Iris Pro Graphics 6200
		#define SMB_BIOS_VERSION	"IM162.88Z.0206.B19.1705011413"
		#define SMB_PRODUCT_NAME	"iMac16,2"
		#define SMB_BOARD_PRODUCT	"Mac-FFE5EF870D7BA81A"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '6', ',', '2' }
	#elif (TARGET_MODEL == IMAC_171) // (Retina 5K, 27-inch, Late 2015)
		// Intel Core i5-6500 @ 3.20 GHz - 4 cores / 4 threads
		// AMD Radeon R9 M380
		#define SMB_BIOS_VERSION	"IM171.88Z.0105.B25.1704292104"
		#define SMB_PRODUCT_NAME	"iMac17,1"
		#define SMB_BOARD_PRODUCT	"Mac-65CE76090165799A"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '7', ',', '1' }
	#elif (TARGET_MODEL == IMAC_181) // Retina 5K, 27-inch, 2017
		#define SMB_BIOS_VERSION	"IM181.88Z.0145.B07.1705082121"
		#define SMB_PRODUCT_NAME	"iMac18,1"
		#define SMB_BOARD_PRODUCT	"Mac-4B682C642B45593E"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '8', ',', '1' }
	#elif (TARGET_MODEL == IMAC_182) // Retina 5K, 27-inch, 2017
		#define SMB_BIOS_VERSION	"IM182.88Z.0145.B07.1705082121"
		#define SMB_PRODUCT_NAME	"iMac18,2"
		#define SMB_BOARD_PRODUCT	"Mac-77F17D7DA9285301"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '8', ',', '2' }
	#else // Defaults to iMac18,3 Retina 5K, 27-inch, 2017
		#define SMB_BIOS_VERSION	"IM183.88Z.0145.B07.1705082121"
		#define SMB_PRODUCT_NAME	"iMac18,3"
		#define SMB_BOARD_PRODUCT	"Mac-BE088AF8C5EB4FA2"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', '1', '8', ',', '3' }
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
		// Intel Core M-5Y51 @ 1.20 GHz (2 cores, 4 threads)
		// Intel Core M-5Y71 @ 1.30 GHz (2 cores, 4 threads)
		#define SMB_BIOS_VERSION	"MB81.88Z.0164.B18.1608121416"
		#define SMB_PRODUCT_NAME	"MacBook8,1"
		#define SMB_BOARD_PRODUCT	"Mac-BE0E8AC46FE800CC"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', '8', ',', '1' }
	#else // Defaults to MacBook9,1
		// Intel Core m3-6Y30 @ 1.10 GHz (2 cores, 4 threads)
		// Intel Core m5-6Y54 @ 1.20 GHz (2 cores, 4 threads)
		// Intel Core m7-6Y75 @ 1.30 GHz (2 cores, 4 threads)
		#define SMB_BIOS_VERSION	"MB91.88Z.0154.B04.1604191425"
		#define SMB_PRODUCT_NAME	"MacBook9,1"
		#define SMB_BOARD_PRODUCT	"Mac-9AE82516C7C6B903"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', '9', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif


#if TARGET_MODEL & MACBOOK_AIR													// 4
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"MacBookAir"

	#if (TARGET_MODEL == MACBOOK_AIR_41)
		// Intel Core i5-2467M @ 1.6GHz (2 cores - 4 threads)
		// Intel Core i7-2677M @ 1.8GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA41.88Z.0077.B14.1510261805"
		#define SMB_PRODUCT_NAME	"MacBookAir4,1"
		#define SMB_BOARD_PRODUCT	"Mac-C08A6BB70A942AC2"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '4', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_AIR_42)
		// Intel Core i5-2557M @ 1.7GHz (2 cores - 4 threads)
		// Intel Core i7-2677M @ 1.8GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA41.88Z.0077.B14.1510261805"
		#define SMB_PRODUCT_NAME	"MacBookAir4,2"
		#define SMB_BOARD_PRODUCT	"Mac-742912EFDBEE19B3"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '4', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_AIR_51)
		// Intel Core i5-3317U @ 1.7GHz (2 cores - 4 threads)
		// Intel Core i7-3667U @ 2.0GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA51.88Z.00EF.B04.1509111654"
		#define SMB_PRODUCT_NAME	"MacBookAir5,1"
		#define SMB_BOARD_PRODUCT	"Mac-66F35F19FE2A0D05"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '5', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_AIR_52)
		// Intel Core i5-3317U @ 1.7GHz (2 cores - 4 threads)
		// Intel Core i7-3667U @ 2.0GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA51.88Z.00EF.B04.1509111654"
		#define SMB_PRODUCT_NAME	"MacBookAir5,2"
		#define SMB_BOARD_PRODUCT	"Mac-2E6FAB96566FE58C"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '5', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_AIR_61)
		// Intel Core i5-3427U @ 1.8GHz (2 cores - 4 threads)
		// Intel Core i7-4650U @ 1.7GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA61.88Z.0099.B22.1602221559"
		#define SMB_PRODUCT_NAME	"MacBookAir6,1"
		#define SMB_BOARD_PRODUCT	"Mac-35C1E88140C3E6CF"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '6', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_AIR_62)
		// Intel Core i5-4250U @ 1.30 GHz (2 cores - 4 threads)
		// Intel Core i7-4650U @ 1.70 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA61.88Z.0099.B22.1602221559"
		#define SMB_PRODUCT_NAME	"MacBookAir6,2"
		#define SMB_BOARD_PRODUCT	"Mac-7DF21CB3ED6977E5"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '6', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_AIR_71)
		// Intel Core i5-5250U @ 1.60 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA71.88Z.0166.B12.1602221953"
		#define SMB_PRODUCT_NAME	"MacBookAir7,1"
		#define SMB_BOARD_PRODUCT	"Mac-9F18E312C5C2BF0B"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'A', 'i', 'r', '7', ',', '1' }
	#else // Defaults to MacBookAir7,2
		// Intel Core i5-5250U @ 1.60 GHz (2 cores - 4 threads)
		// Intel Core i7-5650U @ 2.20 GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MBA71.88Z.0166.B12.1602221953"
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
		#define SMB_BIOS_VERSION	"MBP61.88Z.0057.B11.1509232013"
		#define SMB_PRODUCT_NAME	"MacBookPro6,1"
		#define SMB_BOARD_PRODUCT	"Mac-F22589C8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '6', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_81)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B2C.1510261540"
		#define SMB_PRODUCT_NAME	"MacBookPro8,1"
		#define SMB_BOARD_PRODUCT	"Mac-94245B3640C91C81"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_82)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B2C.1510261540"
		#define SMB_PRODUCT_NAME	"MacBookPro8,2"
		#define SMB_BOARD_PRODUCT	"Mac-94245A3940C91C80"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_83)
		#define SMB_BIOS_VERSION	"MBP81.88Z.0047.B2C.1510261540"
		#define SMB_PRODUCT_NAME	"MacBookPro8,3"
		#define SMB_BOARD_PRODUCT	"Mac-942459F5819B171B"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '8', ',', '3' }
	#elif (TARGET_MODEL == MACBOOK_PRO_91)
		// Intel Core i7-3820QM @ 2.70 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP91.88Z.00D3.B0D.1602221713"
		#define SMB_PRODUCT_NAME	"MacBookPro9,1"
		#define SMB_BOARD_PRODUCT	"Mac-4B7AC7E43945597E"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '9', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_92)
		// Intel Core i7-3820QM @ 2.70 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP91.88Z.00D3.B0D.1602221713"
		#define SMB_PRODUCT_NAME	"MacBookPro9,2"
		#define SMB_BOARD_PRODUCT	"Mac-6F01561E16C75D06"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '9', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_101)
		// Intel Core i7-3635QM @ 2.40 GHz - 4 cores / 8 threads.
		// Intel Core i7-3740QM @ 2.70 GHz - 4 cores / 8 threads.
		// Intel Core i7-3840QM @ 2.80 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP101.88Z.00EE.B0A.1509111559"
		#define SMB_PRODUCT_NAME	"MacBookPro10,1"
		#define SMB_BOARD_PRODUCT	"Mac-C3EC7CD22292981F"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '0', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_102)
		// Intel Core i5-3230QM @ 2.60 GHz - 2 cores / 4 threads.
		// Intel Core i7-3540QM @ 3.00 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP102.88Z.0106.B0A.1509130955"
		#define SMB_PRODUCT_NAME	"MacBookPro10,2"
		#define SMB_BOARD_PRODUCT	"Mac-AFD8A9D944EA4843"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '0', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_111)
		// Intel Core i5-4258U @ 2.40 GHz - 2 cores / 4 threads.
		// Intel Core i5-4288U @ 2.60 GHz - 2 cores / 4 threads.
		// Intel Core i7-4558U @ 2.80 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP111.88Z.0138.B17.1602221718"
		#define SMB_PRODUCT_NAME	"MacBookPro11,1"
		#define SMB_BOARD_PRODUCT	"Mac-189A3D4F975D5FFC"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_112)
		// Intel Core i7-4750HQ @ 2.00 GHz - 4 cores / 8 threads.
		// Intel Core i7-4950HQ @ 2.40 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP112.88Z.0138.B17.1602221600"
		#define SMB_PRODUCT_NAME	"MacBookPro11,2"
		#define SMB_BOARD_PRODUCT	"Mac-3CBD00234E554E41"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '2' }
	#elif (TARGET_MODEL == MACBOOK_PRO_113)
		// Intel Core i7-4850HQ @ 2.30 GHz - 4 cores / 8 threads.
		// Intel Core i7-4960HQ @ 2.60 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP112.88Z.0138.B17.1602221600"
		#define SMB_PRODUCT_NAME	"MacBookPro11,3"
		#define SMB_BOARD_PRODUCT	"Mac-2BD1B31983FE1663"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '3' }
	#elif (TARGET_MODEL == MACBOOK_PRO_114)
		// Intel Core i7-4770HQ @ 2.20 GHz - 4 cores / 8 threads.
		// Intel Core i7-4870HQ @ 2.50 GHz - 4 cores / 8 threads.
		// Intel Core i7-4980HQ @ 2.80 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP114.88Z.0172.B09.1602151732"
		#define SMB_PRODUCT_NAME	"MacBookPro11,3"
		#define SMB_BOARD_PRODUCT	"Mac-06F11FD93F0323C5"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '4' }
	#elif (TARGET_MODEL == MACBOOK_PRO_115)
		// Intel Core i7-4870HQ @ 2.50 GHz - 4 cores / 8 threads.
		// Intel Core i7-4980HQ @ 2.80 GHz - 4 cores / 8 threads.
		#define SMB_BIOS_VERSION	"MBP114.88Z.0172.B09.1602151732"
		#define SMB_PRODUCT_NAME	"MacBookPro11,5"
		#define SMB_BOARD_PRODUCT	"Mac-06F11F11946D27C5"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '1', ',', '5' }
	#elif (TARGET_MODEL == MACBOOK_PRO_121)
		// Intel Core i5-5257U @ 2.70 GHz - 2 cores / 4 threads.
		#define SMB_BIOS_VERSION	"MBP121.88Z.0167.B16.1602111810"
		#define SMB_PRODUCT_NAME	"MacBookPro12,1"
		#define SMB_BOARD_PRODUCT	"Mac-E43C1C25D4880AD6"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '2', ',', '1' }
    #elif (TARGET_MODEL == MACBOOK_PRO_131)
        // 13-inch without Touch Bar / Touch ID
        // Intel Core i5-6360U 2.0 GHz (max Turbo Boost 3.1 GHz)
        // Intel Core i7-6660U 2.4 GHz (max Turbo Boost 3.4 GHz)
        #define SMB_BIOS_VERSION	"MBP131.88Z.0205.B02.1610121536"
        #define SMB_PRODUCT_NAME	"MacBookPro13,1"
        #define SMB_BOARD_PRODUCT	"Mac-473D31EABEB93F9B"
        #define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '3', ',', '1' }
    #elif (TARGET_MODEL == MACBOOK_PRO_132)
        // 13-inch with Touch Bar / Touch ID
        // Intel Core i5-6267U 2.9 GHz (max Turbo Boost 3.3 GHz)
        // Intel Core i5-6287U 3.1 GHz (max Turbo Boost 3.5 GHz)
        // Intel Core i7-6567U 3.3 GHz (max Turbo Boost 3.6 GHz)
        #define SMB_BIOS_VERSION	"MBP132.88Z.0223.B00.1610201042"
        #define SMB_PRODUCT_NAME	"MacBookPro13,2"
        #define SMB_BOARD_PRODUCT	"Mac-66E35819EE2D0D05"
        #define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '3', ',', '2' }
    #elif (TARGET_MODEL == MACBOOK_PRO_133)
        // 15-inch with Touch Bar / Touch ID
        // Intel Core i7-6700HQ 2.6 GHz (max Turbo Boost 3.5 GHz)
        // Intel Core i7-6820HQ 2.7 GHz (max Turbo Boost 3.6 GHz)
        // Intel Core i7-6920HQ 2.9 GHz (max Turbo Boost 3.8 GHz)
        #define SMB_BIOS_VERSION	"MBP133.88Z.0223.B00.1610201042"
        #define SMB_PRODUCT_NAME	"MacBookPro13,3"
        #define SMB_BOARD_PRODUCT	"Mac-A5C67F76ED83108C"
        #define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '3', ',', '3' }
	#elif (TARGET_MODEL == MACBOOK_PRO_141)
		// 13-inch without Touch Bar / Touch ID
		// Intel Core i5-7360U 2.3 GHz (max Turbo Boost 3.6 GHz)
		// Intel Core i7-7660U 2.5 GHz (max Turbo Boost 4.0 GHz)
		#define SMB_BIOS_VERSION	"MBP141.88Z.0160.B00.1705082121"
		#define SMB_PRODUCT_NAME	"MacBookPro14,1"
		#define SMB_BOARD_PRODUCT	"Mac-B4831CEBD52A0C4C"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '4', ',', '1' }
	#elif (TARGET_MODEL == MACBOOK_PRO_142)
		// 13-inch with Touch Bar / Touch ID
		// Intel Core i5-7267U 3.1 GHz (max Turbo Boost 3.5 GHz)
		// Intel Core i5-7287U 3.3 GHz (max Turbo Boost 3.7 GHz)
		// Intel Core i7-7567U 3.5 GHz (max Turbo Boost 4.0 GHz)
		#define SMB_BIOS_VERSION	"MBP142.88Z.0160.B00.1705082121"
		#define SMB_PRODUCT_NAME	"MacBookPro14,2"
		#define SMB_BOARD_PRODUCT	"Mac-CAD6701F7CEA0921 "
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '4', ',', '2' }
	#else // Defaults to MacBookPro14,3
		// 15-inch with Touch Bar / Touch ID
		// Intel Core i7-7700HQ 2.8 GHz (max Turbo Boost 3.8 GHz)
		// Intel Core i7-7820HQ 2.9 GHz (max Turbo Boost 3.9 GHz)
		// Intel Core i7-7920HQ 3.1 GHz (max Turbo Boost 4.1 GHz)
		#define SMB_BIOS_VERSION	"MBP143.88Z.0160.B00.1705090111"
		#define SMB_PRODUCT_NAME	"MacBookPro14,3"
		#define SMB_BOARD_PRODUCT	"Mac-551B86E5744E2388"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', '1', '4', ',', '3' }
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
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B14.1510261805"
		#define SMB_PRODUCT_NAME	"Macmini5,1"
		#define SMB_BOARD_PRODUCT	"Mac-8ED6AF5B48C039E1"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '1' }
	#elif (TARGET_MODEL == MACMINI_52)
		// Intel Core i5-2520M @ 2.5GHz (2 cores - 4 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B14.1510261805"
		#define SMB_PRODUCT_NAME	"Macmini5,2"
		#define SMB_BOARD_PRODUCT	"Mac-4BC72D62AD45599E"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '2' }
	#elif (TARGET_MODEL == MACMINI_53)
		// Intel Core i7-2635QM @ 2.0GHz (4 cores - 8 threads)
		#define SMB_BIOS_VERSION	"MM51.88Z.0077.B14.1510261805"
		#define SMB_PRODUCT_NAME	"Macmini5,3"
		#define SMB_BOARD_PRODUCT	"Mac-7BA5B2794B2CDB12"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '5', ',', '3' }
	#elif (TARGET_MODEL == MACMINI_61)
		// Intel Core i5-3210M @ 2.50 GH (2 cores - 4 theeads)
		#define SMB_BIOS_VERSION	"MM61.88Z.0106.B0A.1509111654"
		#define SMB_PRODUCT_NAME	"Macmini6,1"
		#define SMB_BOARD_PRODUCT	"Mac-031AEE4D24BFF0B1"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '6', ',', '1' }
	#elif (TARGET_MODEL == MACMINI_62)
		// Intel Core i7-3615QM @ 2.30 GHz (4 cores - 8 threads)
		#define SMB_BIOS_VERSION	"MM61.88Z.0106.B0A.1509111654"
		#define SMB_PRODUCT_NAME	"Macmini6,2"
		#define SMB_BOARD_PRODUCT	"Mac-F65AE981FFA204ED"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'm', 'i', 'n', 'i', '6', ',', '2' }
	#else // Defaults to Macmini7,1
		#define SMB_BIOS_VERSION	"MM71.88Z.0220.B07.1602221546"
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
		#define SMB_BIOS_VERSION	"MP41.88Z.0081.B08.1001221313"
		#define SMB_PRODUCT_NAME	"MacPro4,1"
		#define SMB_BOARD_PRODUCT	"Mac-F221BEC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '4', ',', '1' }
	#elif (TARGET_MODEL == MACPRO_51)
		#define SMB_BIOS_VERSION	"MP51.88Z.007F.B03.1010071432"
		#define SMB_PRODUCT_NAME	"MacPro5,1"
		#define SMB_BOARD_PRODUCT	"Mac-F221BEC8"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '5', ',', '1' }
	#else // Defaults to MacPro6,1
		#define SMB_BIOS_VERSION	"MP61.88Z.0116.B20.1610051057"
		#define SMB_PRODUCT_NAME	"MacPro6,1"
		#define SMB_BOARD_PRODUCT	"Mac-F60DEB81FF30ACF6"
		#define EFI_MODEL_NAME		{ 'M', 'a', 'c', 'P', 'r', 'o', '6', ',', '1' }
	#endif
// -------------------------------------------------------------------------------------
#endif

#if TARGET_MODEL & IMACPRO														// 64
// -------------------------------------------------------------------------------------
	#define SMB_FAMILY	"iMacPro"

	#if (TARGET_MODEL == IMACPRO_10)
		#define SMB_BIOS_VERSION	"IMP10.88Z.0058.B00.1705091711"
		#define SMB_PRODUCT_NAME	"iMacPro1,1"
		#define SMB_BOARD_PRODUCT	"Mac-CF21D135A7D34AA6"
		#define EFI_MODEL_NAME		{ 'i', 'M', 'a', 'c', 'P', 'r', 'o', '1', ',', '0' }
	#endif
// -------------------------------------------------------------------------------------
#endif
