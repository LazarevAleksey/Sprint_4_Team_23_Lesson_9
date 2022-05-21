//Вставьте сюда своё решение из урока «‎Очередь запросов».‎
#include "document.h"

using namespace std;


	Document::Document() = default;
	Document::Document(int id, double relevance, int rating)
		: id(id)
		, relevance(relevance)
		, rating(rating) {
	}

	std::ostream& operator<<(std::ostream& out, const Document& document) {
		out << "{ "s
			<< "document_id = "s << document.id << ", "s
			<< "relevance = "s << document.relevance << ", "s
			<< "rating = "s << document.rating << " }"s;
		return out;
	}

	void PrintDocument(const Document& document) {
		cout << "{ "s
			<< "document_id = "s << document.id << ", "s
			<< "relevance = "s << document.relevance << ", "s
			<< "rating = "s << document.rating << " }"s << endl;
	}

	void PrintMatchDocumentResult(int document_id, const std::vector<std::string>& words, DocumentStatus status) {
		cout << "{ "s
			<< "document_id = "s << document_id << ", "s
			<< "status = "s << static_cast<int>(status) << ", "s
			<< "words ="s;
		for (const std::string& word : words) {
			cout << ' ' << word;
		}
		cout << "}"s << endl;
	}

	void AddDocument(SearchServer& search_server, int document_id, const std::string& document,
		DocumentStatus status, const std::vector<int>& ratings) {
		try {
			search_server.AddDocument(document_id, document, status, ratings);
		}
		catch (const exception& e) {
			cout << "Error in adding document "s << document_id << ": "s << e.what() << endl;
		}
	}

	void FindTopDocuments(const SearchServer& search_server, const std::string& raw_query) {
		cout << "Results for request: "s << raw_query << endl;
		try {
			for (const Document& document : search_server.FindTopDocuments(raw_query)) {
				PrintDocument(document);
			}
		}
		catch (const exception& e) {
			cout << "Error is seaching: "s << e.what() << endl;
		}
	}

	void MatchDocuments(const SearchServer& search_server, const std::string& query) {
		try {
			cout << "Matching for request: "s << query << endl;
			const int document_count = search_server.GetDocumentCount();
			for (int index = 0; index < document_count; ++index) {
				const int document_id = search_server.GetDocumentId(index);
				const auto [words, status] = search_server.MatchDocument(query, document_id);
				PrintMatchDocumentResult(document_id, words, status);
			}
		}
		catch (const exception& e) {
			cout << "Error in matchig request "s << query << ": "s << e.what() << endl;
		}
	}