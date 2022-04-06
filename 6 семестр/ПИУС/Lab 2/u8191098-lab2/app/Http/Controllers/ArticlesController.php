<?php

namespace App\Http\Controllers;

use App\Models\Article;
use App\Models\Tag;
use Illuminate\Http\Request;

class ArticlesController extends Controller
{
    public function getAllArticles(Request $request)
    {
        $filterTitle = $request->query('filterTitle');
        $filterSymbolCode = $request->query('filterSymbolCode');
        $filterTag = $request->query('filterTag');

        $articles = Article::where('articles.title', 'like', '%' . $filterTitle . '%')
            ->where('articles.symbol_code', 'like', '%' . $filterSymbolCode . '%')
            ->whereHas('tags', function ($tag) use ($filterTag) {
                $tag->where('name', 'like', '%' . $filterTag . '%');
            })
            ->paginate(15);

        return view('articles.articlesList')
            ->with('articles', $articles)
            ->with('filterSymbolCode', $filterSymbolCode)
            ->with('filterTitle', $filterTitle)
            ->with('filterTag', $filterTag);
    }

    public function getArticleInfo($id)
    {
        $article = Article::findOrFail($id);
        $tags = $article->tags()
        ->orderBy('name', 'asc')->get();

        return view('articles.articleInfo')
            ->with('article', $article)
            ->with('tags', $tags);
    }
}
