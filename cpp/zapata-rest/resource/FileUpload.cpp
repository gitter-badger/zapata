#include <resource/FileUpload.h>

zapata::FileUpload::FileUpload() :
	zapata::RESTController("^/file/upload$") {
}

zapata::FileUpload::~FileUpload() {
}

void zapata::FileUpload::post(zapata::HTTPReq& _req, zapata::HTTPRep& _rep) {
	{
		string _body = _req->body();
		assertz(_body.length() != 0, "Body entity must be provided.", zapata::HTTP412);

		assertz(_req->header("Content-Type").find("application/json") != string::npos, "Body entity must be 'application/json'", zapata::HTTP406);

		zapata::JSONObj _params;
		zapata::fromstr(_body, _params);

		assertz(!!_params["uploaded_file"], "The 'uploaded_file' parameter must be provided.", zapata::HTTP412);

		string _from((string) _params["uploaded_file"]);
		string _to((string) this->configuration()["zapata"]["rest"]["uploads"]["upload_path"]);
		zapata::normalize_path(_to, true);

		string _originalname(_req->header("X-Original-Filename"));
		string _path;
		string _name;
		string _mime;
		do {
			string _dir(_to);
			_path.assign("");
			zapata::generate_hash(_path);
			_dir.insert(_dir.length(), _path);
			zapata::mkdir_recursive(_dir, 0777);
			_path.insert(_path.length(), "/");

			if (_originalname.length() != 0) {
				_path.insert(_path.length(), _originalname);

				_mime.assign(_req->header("X-Original-Mimetype"));
				if (_mime.length() != 0) {
					_mime.assign(_mime.substr(0, _mime.find(";")));
				}
			}
			else {
				zapata::MIMEType _m = zapata::get_mime((string) _params["uploaded_file"]);
				_path.insert(_path.length(), "_uploaded");
				_path.insert(_path.length(), zapata::mimetype_extensions[_m]);

				_mime.assign(zapata::mimetype_names[_m]);
			}

			_name.assign(_path);
			_path.insert(0, _to);
		}
		while (zapata::path_exists(_path));

		string _encoding(_req->header("X-Content-Transfer-Encoding"));
		transform(_encoding.begin(), _encoding.end(), _encoding.begin(), ::toupper);
		if (_encoding == "BASE64") {
			ifstream _ifs;
			_ifs.open(_from.data());
			ofstream _ofs;
			_ofs.open(_path.data());

			zapata::base64_decode(_ifs, _ofs);

			_ifs.close();
			_ofs.flush();
			_ofs.close();
		}
		else {
			assertz(zapata::copy_path((string ) _params["uploaded_file"], _path), "There was an error copying the temporary file to the 'upload_path' directory.", zapata::HTTP500);
		}

		string _location((string) this->configuration()["zapata"]["rest"]["uploads"]["upload_url"]);
		zapata::normalize_path(_location, true);
		_location.insert(_location.length(), _name);

		_rep->status(zapata::HTTP201);
		_rep << "X-File-Mimetype" << _mime;
		_rep << "Location" << _location;
	}
}