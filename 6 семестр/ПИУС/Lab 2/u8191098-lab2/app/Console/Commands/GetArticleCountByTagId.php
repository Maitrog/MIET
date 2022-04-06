<?php

namespace App\Console\Commands;

use Illuminate\Console\Command;
use App\Models\Tag;
use Illuminate\Database\Eloquent\ModelNotFoundException;

class GetArticleCountByTagId extends Command
{
    /**
     * The name and signature of the console command.
     *
     * @var string
     */
    protected $signature = 'article:countByTag {id}';

    /**
     * The console command description.
     *
     * @var string
     */
    protected $description = 'Get article count by tag id';

    /**
     * Execute the console command.
     *
     * @return int
     */
    public function handle()
    {
        try
        {
            $id = $this->argument('id');
            $tags = Tag::findOrFail($id);
            $articleCount = $tags->articles()
            ->get()->count();
            $this->line('Tag with id ' . $id . ' has ' . $articleCount . ' article(s)');
        }
        catch(ModelNotFoundException $e)
        {
            $this->line('Tag with id ' . $id . ' doesn\'t exist');
        }
        return 0;
    }
}
