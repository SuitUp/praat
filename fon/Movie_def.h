/* Movie_def.h
 *
 * Copyright (C) 2011,2015 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#define ooSTRUCT Movie
oo_DEFINE_CLASS (Movie, Sampled)

	oo_AUTO_OBJECT (Sound, 2, d_sound)
	oo_STRING (d_folderName)
	oo_AUTO_OBJECT (Strings, 0, d_fileNames)

	#if oo_DECLARING
		void v_info ()
			override;
	#endif

oo_END_CLASS (Movie)
#undef ooSTRUCT


/* End of file Movie_def.h */
