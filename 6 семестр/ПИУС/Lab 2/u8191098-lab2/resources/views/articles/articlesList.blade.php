<html>
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet"
    integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

<body>
    <h1>Articles</h1>

    <form class="form-inline" method="GET">
        <div class="form-group mb-2">
            <label for="filterTitle" class="col-sm-2 col-form-label">Filter title</label>
            <input type="text" class="form-control" id="filterTitle" name="filterTitle" placeholder="Article title..."
                value="{{ $filterTitle }}">
        </div>
				<div class="form-group mb-2">
					<label for="filterSymbolCode" class="col-sm-2 col-form-label">Filter symbol code</label>
					<input type="text" class="form-control" id="filterSymbolCode" name="filterSymbolCode" placeholder="Article symbol code..."
							value="{{ $filterSymbolCode }}">
			</div>
			<div class="form-group mb-2">
				<label for="filterTag" class="col-sm-2 col-form-label">Filter tag</label>
				<input type="text" class="form-control" id="filterTag" name="filterTag" placeholder="Article tag..."
						value="{{ $filterTag }}">
		</div>
        <button type="submit" class="btn btn-default mb-2">Find</button>
    </form>

    <table class="table table-bordered table-hover">
        <thead>
            <tr>
                <td>Id</td>
                <td>Title</td>
                <td>Symbol Code</td>
                <td>Content</td>
                <td>Created at</td>
                <td>Autor</td>
            </tr>
        </thead>
        <tbody>
            @if ($articles->count() == 0)
                <tr>
                    <td colspan="5">No articles to display.</td>
                </tr>
            @endif

            @foreach ($articles as $article)
                <tr>
                    <td>{{ $article->id }}</td>
                    <td>{{ $article->title }}</td>
                    <td>{{ $article->symbol_code }}</td>
                    <td>{{ $article->content }}</td>
                    <td>{{ $article->created_at }}</td>
                    <td>{{ $article->autor }}</td>
                </tr>
            @endforeach
        </tbody>
    </table>
</body>
{!! $articles->appends(Request::except('page'))->render('pagination::bootstrap-5') !!}

</html>
